cmake_minimum_required(VERSION 3.20)
project(hello_sfml VERSION 0.0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

## Setup Conan
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
      "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP NO_OUTPUT_DIRS BUILD missing)


## Find third-party packages
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})
find_package(sfml REQUIRED)


## Target
target_link_libraries(${PROJECT_NAME} PRIVATE sfml::sfml)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)


## Copy resources
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/share DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
