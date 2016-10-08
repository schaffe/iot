cmake_minimum_required(VERSION 2.8.4)
set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")

#git@github.com:altexdim/arduino-cmake.git
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/../arduino-cmake/cmake/ArduinoToolchain.cmake)

#link_directories(../arduino-base)
include_directories(../arduino-base)

#https://github.com/kastrulya/OneButton
link_directories(../libs/OneButton)
#set(HEADER_FILES ../arduino-base/Base.h ${HEADER_FILES})
set(PROJECT_NAME clap-blinker)

project(${PROJECT_NAME})

set(${CMAKE_PROJECT_NAME}_SRCS Main.cpp)
set(${CMAKE_PROJECT_NAME}_BOARD uno)
set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyACM0)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})