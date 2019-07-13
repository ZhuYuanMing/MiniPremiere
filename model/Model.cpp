#include "./Model.h"

std::shared_ptr<EditableVideo> Model::openFile(const std::string path) {
    currentVideo = std::make_shared<EditableVideo>(path);
    return currentVideo;
}