cmake_minimum_required(VERSION 3.19)
project(hello_qt VERSION 0.0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

## Setup Conan
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
      "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
#conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP NO_OUTPUT_DIRS BUILD missing)
# Run manually from ./build: conan install .. --build=missing --profile=Gcc8

## Find third-party packages
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})
#find_package(fmt REQUIRED)
find_package(Qt6 REQUIRED)

#message(STATUS ${Qt5_LIBRARIES})

## Target
target_link_libraries(${PROJECT_NAME} PRIVATE #[[fmt::fmt]] Qt6::Qt6)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
