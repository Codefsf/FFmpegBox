cmake_minimum_required(VERSION 3.5)

project(FFmpegBox LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets  REQUIRED)

#不同平台源文件
if(WIN32)
    message("os:win32")
    add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
elseif(Unix)
    message("os:unix")
elseif(APPLE)
    message("os:mac")
endif()

#不同平台依赖库
if(WIN32)
    message("link os:win32")
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
elseif(Unix)
    message("link os:unix")
elseif(APPLE)
    message("link os:mac")
endif()

