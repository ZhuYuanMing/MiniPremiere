//
// Created by px on 7/9/2019.
//

#ifndef EDITABLEVIDEO_H
#define EDITABLEVIDEO_H
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QImage>
extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include "libavutil/mathematics.h"
#include <libavutil/samplefmt.h>
#include <libavutil/pixfmt.h>
}

class EditableVideo{
private:
    int64_t duration = 0;
    int64_t currentTime = 0;
    int VideoFps = 0;
    bool playing = false;  //deprecated

    AVPacket        currentPacket;
    AVFormatContext *pFormatContext = nullptr;
    AVFrame         *currentFrame;
    AVCodecContext  *pCodecContext;
    AVFrame         *currentFrameRGB;
    std::shared_ptr<cv::Mat> currentMatPointer;
    int video_stream_index = -1;
    int frameFinished = 0;
    int64_t prepts = 0;
    int             numBytes;
    uint8_t         *buffer;

    void CopyDate(AVFrame *pFrame,int width,int height,int64_t time);
    static void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame);
public:
    explicit EditableVideo(std::string srcPath);
    ~EditableVideo();
    std::shared_ptr<cv::Mat> getNextImage();
    inline int64_t getCurrentTime(){return currentTime;}
    inline int GetFps(){return VideoFps;}
    inline int64_t GetDuration(){return duration;}
    //cv::Mat seekImage(int64_t timeStamp);
};
#endif //EDITABLEVIDEO_H
