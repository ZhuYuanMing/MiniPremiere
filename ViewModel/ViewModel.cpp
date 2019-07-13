//
// Created by px on 7/13/2019.
//

#include "ViewModel.h"
#include "./commands/OpenFileCommand.h"
#include "./commands/FetchQimageCommand.h"

ViewModel::ViewModel(){
    model = std::make_shared<Model>();
    opFileCommand = std::make_shared<OpenFileCommand>(this);
    fQimageCommand = std::make_shared<FetchQimageCommand>(this);
    q_image = std::make_shared<QImage>();
    VideoDuration = std::make_shared<int>();
    VideoFps = std::make_shared<int>();
}