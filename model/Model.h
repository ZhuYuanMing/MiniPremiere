//
// Created by px on 7/8/2019.
//

#ifndef MODEL_H
#define MODEL_H


#include "./EditableVideo.h"
class Model {
private:
    std::shared_ptr<EditableVideo> currentVideo;
public:
    Model()= default;
    ~Model(){currentVideo.reset();}
    std::shared_ptr<EditableVideo> openFile(const std::string path);
};




#endif //MODEL_H

