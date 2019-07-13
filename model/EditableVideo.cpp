#include "./EditableVideo.h"
EditableVideo::~EditableVideo(){
    currentMatPointer.reset();
    av_free(buffer);
    av_free(currentFrameRGB);

    av_free(currentFrame);
    avcodec_close(pCodecContext);
    avformat_close_input(&pFormatContext);

}

EditableVideo::EditableVideo(std::string srcPath) {
    pFormatContext = avformat_alloc_context();
    if (!pFormatContext) {
        printf("ERROR could not allocate memory for Format Context");
        exit(1);
    }
    if (avformat_open_input(&pFormatContext, srcPath.c_str(), nullptr, nullptr) != 0) {
        printf("ERROR could not open the file");
        exit(1);
    }


    this->duration = pFormatContext->duration;
    this->currentTime = 0;
    this->playing = false;
    this->currentFrame = av_frame_alloc();
    this->currentFrameRGB = av_frame_alloc();

    //malloc a part of memory to store original data while converting


    printf("format %s, duration %lld us, bit_rate %lld", pFormatContext->iformat->name, pFormatContext->duration, pFormatContext->bit_rate);
    if (avformat_find_stream_info(pFormatContext,  nullptr) < 0) {
        printf("ERROR could not get the stream info");
        exit(1);
    }
    //find first video stream
    AVCodec *pCodec = nullptr;
    AVCodecParameters *pCodecParameters =  nullptr;

    for (int i = 0; i < pFormatContext->nb_streams; i++){
        AVCodecParameters *pLocalCodecParameters =  nullptr;
        pLocalCodecParameters = pFormatContext->streams[i]->codecpar;
        AVCodec *pLocalCodec = nullptr;
        // finds the registered decoder for a codec ID
        pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);
        if (pLocalCodec==nullptr) {
            printf("ERROR unsupported codec!");
            exit(1);
        }
        // when the stream is a video we store its index, codec parameters and codec
        if(pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO){
            if (this->video_stream_index == -1) {
                this->video_stream_index = i;
                pCodec = pLocalCodec;
                pCodecParameters = pLocalCodecParameters;
                this->pCodecContext = pFormatContext->streams[i]->codec;
                if(avcodec_open2(pCodecContext, pCodec, 0) < 0){ //open video decoder
                    throw "error";
            }
                this->VideoFps = av_q2d(pFormatContext->streams[i]->r_frame_rate);
                printf("VideoFps is %d",this->VideoFps);
            }
        }

        //audio codec
        if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO) {
            printf("Audio Codec: %d channels, sample rate %d", pLocalCodecParameters->channels, pLocalCodecParameters->sample_rate);
        }

        // print its name, id and bitrate
        //printf("\tCodec %s ID %d bit_rate %lld", pLocalCodec->name, pLocalCodec->id, pCodecParameters->bit_rate);
    }

    numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, pCodecContext->width, pCodecContext->height);
    buffer = (uint8_t *)av_malloc( numBytes*sizeof(uint8_t));
    avpicture_fill((AVPicture *)currentFrameRGB, buffer, AV_PIX_FMT_RGB24,pCodecContext->width, pCodecContext->height);
}

std::shared_ptr<cv::Mat> EditableVideo::getNextImage() {
    while(1){
        if(av_read_frame(this->pFormatContext, &this->currentPacket) >= 0){
            if(this->currentPacket.stream_index == this->video_stream_index){ //judge if video data
                avcodec_decode_video2(pCodecContext, currentFrame, &frameFinished, &currentPacket);
                if(frameFinished){
                    static struct SwsContext *img_convert_ctx;
                    if(img_convert_ctx == NULL) {
                        int w = pCodecContext->width;
                        int h = pCodecContext->height;
                        img_convert_ctx = sws_getContext(w, h, pCodecContext->pix_fmt, w, h, AV_PIX_FMT_RGB24, SWS_BICUBIC,NULL, NULL, NULL);
                        if(img_convert_ctx == NULL) {
                            fprintf(stderr, "Cannot initialize the conversion context!\n");
                            exit(1);
                        }
                    }
                    //convert YUV420p image to BRG24
                    sws_scale(img_convert_ctx, currentFrame->data, currentFrame->linesize, 0, pCodecContext->height, currentFrameRGB->data, currentFrameRGB->linesize);
                    CopyDate(currentFrameRGB, pCodecContext->width, pCodecContext->height,currentPacket.pts-prepts);
                    prepts = currentPacket.pts;
                    return currentMatPointer;
                }
                av_packet_unref(&currentPacket);
                break;
            }
            av_packet_unref(&currentPacket);
        }
        else{
            std::shared_ptr<cv::Mat> blackPhoto = std::make_shared<cv::Mat>(cv::Size(pCodecContext->width, pCodecContext->height), CV_8UC3, cv::Scalar(0));
            currentMatPointer = blackPhoto;
            return currentMatPointer;
        }
    }

}

void EditableVideo::CopyDate(AVFrame *pFrame, int width, int height, int64_t time) {
    if(time <=0 ) time = 1;

    int		nChannels;
    size_t		stepWidth;
    uchar  *	pData;
    std::shared_ptr<cv::Mat> frameImage = std::make_shared<cv::Mat>(cv::Size(width, height), CV_8UC3, cv::Scalar(0));
    stepWidth = frameImage->step;
    nChannels = frameImage->channels();
    pData = frameImage->data;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            pData[i * stepWidth + j * nChannels + 0] = pFrame->data[0][i * pFrame->linesize[0] + j * nChannels + 2];
            pData[i * stepWidth + j * nChannels + 1] = pFrame->data[0][i * pFrame->linesize[0] + j * nChannels + 1];
            pData[i * stepWidth + j * nChannels + 2] = pFrame->data[0][i * pFrame->linesize[0] + j * nChannels + 0];
        }
    }
    currentMatPointer = frameImage;

}

void EditableVideo::SaveFrame(AVFrame *pFrame, int width, int height, int iFrame) {
    FILE *pFile;
    char szFilename[32];
    int  y;

    // Open file
    sprintf(szFilename, "frame%d.ppm", iFrame);
    pFile=fopen(szFilename, "wb");
    if(pFile==NULL)
        return;

    // Write header
    fprintf(pFile, "P6\n%d %d\n255\n", width, height);

    // Write pixel data
    for(y=0; y<height; y++)
        fwrite(pFrame->data[0]+y*pFrame->linesize[0], 1, width*3, pFile);

    // Close file
    fclose(pFile);
}