cmake_minimum_required(VERSION 3.24)

project(hello_sfml VERSION 0.0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

## Find third-party packages
find_package(SFML REQUIRED)


## Target
target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBRARIES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)


## Copy resources
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/share DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
