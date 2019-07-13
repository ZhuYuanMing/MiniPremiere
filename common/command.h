#ifndef COMMAND_H
#define COMMAND_H

#include<string>

class CommandBase{
public:
    virtual void SetParameters(const std::string path) = 0;
    virtual void Exec() = 0;
};
#endif //COMMAND_H
