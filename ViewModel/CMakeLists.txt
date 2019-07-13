# set global info of cmake
cmake_minimum_required(VERSION 3.12)
project(view_model_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


if(WIN32)
    include_directories(C:/CodeLibrary/opencv-3.4.6/build/install/include)
    include_directories(C:/CodeLibrary/ffmpeg-4.1.3-win64-dev/include)
    include_directories(C:\\Qt\\5.13.0\\mingw73_64\\include)
    link_directories(C:/CodeLibrary/ffmpeg-4.1.3-win64-dev/lib)
    set(CMAKE_PREFIX_PATH C:/Qt/5.13.0/mingw73_64/lib/cmake  C:/CodeLibrary/opencv-3.4.6/build/install)
endif(WIN32)

# find and set Qt
find_package(Qt5Gui REQUIRED)


# find and set openCV
find_package(OpenCV)
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# set ffmpeg
set(ffmpeg_LIBS avcodec avformat avutil avdevice swscale)

#aux_source_directory(. SOURCE_FILES)
#aux_source_directory(./commands SOURCE_FILES)
#aux_source_directory(../model SOURCE_FILES)
set(SOURCE_FILES
        ./testViewModel.cpp
        ./commands/OpenFileCommand.cpp
        ./commands/FetchQimageCommand.cpp
        ./ViewModel.cpp
        ../model/Model.cpp
        ../model/EditableVideo.cpp)
#link
add_executable(view_model_test ${SOURCE_FILES})
target_link_libraries(view_model_test ${OpenCV_LIBS} ${ffmpeg_LIBS}  Qt5::Gui )


