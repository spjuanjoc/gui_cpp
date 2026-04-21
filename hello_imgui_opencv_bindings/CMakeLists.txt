cmake_minimum_required(VERSION 3.20)

project(hello_imgui_opencv_bindings
  VERSION "1.0.0"
  DESCRIPTION "Hello ImGui with OpenCV"
  LANGUAGES CXX
)

## Set the project as an executable target
add_executable(${PROJECT_NAME}
  src/bindings/imgui-SFML.cpp
  src/main.cpp
)


## Find third-party packages
find_package(fmt REQUIRED)
find_package(imgui REQUIRED)
find_package(OpenCV REQUIRED)
find_package(SFML REQUIRED)


## Target
target_include_directories(${PROJECT_NAME}
  SYSTEM PRIVATE
    ${fmt_INCLUDES}
    ${imgui_INCLUDES}
    ${opencv_INCLUDES}
    ${SFML_INCLUDES}
  PUBLIC
    include
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${fmt_LIBRARIES}
    ${imgui_LIBRARIES}
    ${opencv_LIBRARIES}
    ${SFML_LIBRARIES}
)


## Copy resources
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/share DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
