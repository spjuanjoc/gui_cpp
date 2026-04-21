cmake_minimum_required(VERSION 3.19)
project(hello_gtk4 VERSION 0.0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)


## Find third-party packages
find_package(gtk REQUIRED)


## Target
target_link_libraries(${PROJECT_NAME} PRIVATE ${gtk_LIBRARIES})
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${gtk_INCLUDE_DIRS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
