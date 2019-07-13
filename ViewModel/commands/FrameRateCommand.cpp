//
// Created by px on 7/13/2019.
//
#include "./FrameRateCommand.h"
#include "../ViewModel.h"
FrameRateCommand::FrameRateCommand(ViewModel *ptr){
    this->PtrViewModel = ptr;
}

void FrameRateCommand::Exec() {
    PtrViewModel->
}

void FrameRateCommand::SetParameters(const std::string path) {
    ;
}