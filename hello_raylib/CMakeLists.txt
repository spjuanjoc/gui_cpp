cmake_minimum_required(VERSION 3.24)

project(hello_raylib VERSION 0.0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)


## Find third-party packages
find_package(raylib REQUIRED)


## Target
target_link_libraries(${PROJECT_NAME} PRIVATE ${raylib_LIBRARIES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
