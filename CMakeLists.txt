cmake_minimum_required(VERSION 3.5)

project(subtitles_anywhere VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT WIN32)
    message(FATAL_ERROR "This project can only be built on Windows.")
endif()

if (MSVC)
    if(MSVC_TOOLSET_VERSION LESS 141)
        message(FATAL_ERROR "Only Microsoft Visual Studio 17 and newer are supported!")
    endif()
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_subdirectory(src)
