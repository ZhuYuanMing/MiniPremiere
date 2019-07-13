//
// Created by px on 7/13/2019.
//
#include "./FetchQimageCommand.h"
#include "../ViewModel.h"

FetchQimageCommand::FetchQimageCommand(ViewModel *ptr){
    this->PtrViewModel = ptr;
}

void FetchQimageCommand::Exec() {
    PtrViewModel->ExecFetchQimageCommand();
}

void FetchQimageCommand::SetParameters(const std::string path) {
    ;
}