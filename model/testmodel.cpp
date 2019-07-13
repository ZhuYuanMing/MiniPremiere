//
// Created by px on 7/9/2019.
//
#include "./Model.h"

int main(){

    Model testModel;
    std::shared_ptr<EditableVideo> testVideo;
    testVideo = testModel.openFile("C:\\Users\\px\\Desktop\\test.mp4");
    std::shared_ptr<cv::Mat> testMat;
    for(int i=0;i<500;i++){
        testMat = testVideo->getNextImage();
        cv::namedWindow("Video", CV_WINDOW_AUTOSIZE);
        cv::imshow("Video", *testMat);
        cv::waitKey(10);
    }
}
