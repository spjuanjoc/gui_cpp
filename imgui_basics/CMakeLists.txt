cmake_minimum_required(VERSION 3.19)
project(imgui_basics VERSION "0.0.1" LANGUAGES CXX)

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
find_package(fmt REQUIRED)
find_package(ImGui-SFML REQUIRED)


## Target
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML fmt::fmt)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
#target_include_directories(${PROJECT_NAME} PRIVATE ${imgui_INCLUDES})

#message(STATUS "imgui_INCLUDES ${imgui_INCLUDES}")

## Copy resources
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/share DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
