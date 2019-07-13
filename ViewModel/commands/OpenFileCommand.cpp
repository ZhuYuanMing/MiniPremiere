//
// Created by px on 7/13/2019.
//
#include "./OpenFileCommand.h"
#include "../ViewModel.h"

OpenFileCommand::OpenFileCommand(ViewModel *ptr){
    this->PtrViewModel = ptr;
}

void OpenFileCommand::Exec() {
    PtrViewModel->ExecOpenFileCommand(Para_Path);
}
void OpenFileCommand::SetParameters(const std::string path) {
    this->Para_Path = path;
}