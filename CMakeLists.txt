cmake_minimum_required(VERSION 3.5)

project(FFmpegBox LANGUAGES CXX)

set(CMAKE_GENERATOR_PLATFORM x64)
set(CMAKE_GENERATOR_TOOLSET x64)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "D:/Qt/6.6.1/msvc2019_64/lib/cmake")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if(WIN32)
    message("include os:win32")
    
elseif(Unix)
    message("include os:unix")
elseif(APPLE)
    message("include os:mac")
endif()


#不同平台源文件
if(WIN32)
    message("os:win32")

    FILE(GLOB global
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui

        src/ffmpeg-filter.cpp
        src/ffmpeg-filter.h
    )
    source_group("" FILES ${global})

    set(ALL_SOURCE_FILES
        ${global}
    )

    #生成目标文件
    add_executable(${PROJECT_NAME} ${ALL_SOURCE_FILES})
elseif(Unix)
    message("os:unix")
elseif(APPLE)
    message("os:mac")
endif()

#不同平台依赖库
if(WIN32)
    message("link os:win32")

    include_directories(
        ${PROJECT_SOURCE_DIR}/incoming/ffmpeg/
        ${PROJECT_SOURCE_DIR}/incoming/ffmpeg/include/
    )
    message("include dir:${PROJECT_SOURCE_DIR}/incoming/ffmpeg/include/")


    target_link_directories(${PROJECT_NAME} PRIVATE
        "${PROJECT_SOURCE_DIR}/incoming/ffmpeg/libs/"
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE 
        Qt6::Widgets
        avfilter
        swscale
        avcodec
        avdevice
        avformat
        avutil
        swresample
    )
elseif(Unix)
    message("link os:unix")
elseif(APPLE)
    message("link os:mac")
endif()

