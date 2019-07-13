# set global info of cmake
cmake_minimum_required(VERSION 3.12)
project(model_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


if(WIN32)
    include_directories(C:/CodeLibrary/opencv-3.4.6/build/install/include)
    include_directories(C:/CodeLibrary/ffmpeg-4.1.3-win64-dev/include)
    link_directories(C:/CodeLibrary/ffmpeg-4.1.3-win64-dev/lib)
    set(CMAKE_PREFIX_PATH C:/Qt/5.13.0/mingw73_64/lib/cmake  C:/CodeLibrary/opencv-3.4.6/build/install)
endif(WIN32)
# find and set Qt
find_package(Qt5Gui REQUIRED)

# find and set openCV
find_package(OpenCV)
set(OpenCV_LIBS opencv_core  opencv_highgui)
# set ffmpeg
set(ffmpeg_LIBS avcodec avformat avutil avdevice swscale)


set(SOURCE_FILES ./testmodel.cpp  ./Model.cpp  ./EditableVideo.cpp)
#link
add_executable(model_test ${SOURCE_FILES})
target_link_libraries(model_test ${OpenCV_LIBS} ${ffmpeg_LIBS} Qt5::Gui)


