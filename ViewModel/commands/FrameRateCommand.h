//
// Created by px on 7/13/2019.
//

#ifndef FRAMERATECOMMAND_H
#define FRAMERATECOMMAND_H

#include "../../common/Command.h"

class ViewModel;
class FrameRateCommand : public  CommandBase{
private:
    ViewModel *PtrViewModel;
public:
    FrameRateCommand(ViewModel *ptr);
    ~FrameRateCommand()= default;
    virtual void Exec();
    virtual void SetParameters(const std::string path);
};


#endif //FRAMERATECOMMAND_H
