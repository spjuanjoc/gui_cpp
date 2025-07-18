cmake_minimum_required(VERSION 3.24)

project(hello_imgui_opencv
  VERSION "1.0.0"
  DESCRIPTION "Hello ImGui with OpenCV"
  LANGUAGES CXX
)

## Set the project as an executable target
add_executable(${PROJECT_NAME}
  src/main.cpp
)


## Find third-party packages
find_package(fmt REQUIRED)
find_package(imgui REQUIRED)
find_package(OpenCV REQUIRED)
find_package(SFML REQUIRED)
find_package(ImGui-SFML REQUIRED)


## Target
target_include_directories(${PROJECT_NAME}
  SYSTEM PRIVATE
    ${fmt_INCLUDES}
    ${imgui_INCLUDES}
    ${OpenCV_INCLUDES}
    ${SFML_INCLUDES}
    ${ImGui-SFML_INCLUDES}
  PUBLIC
    include
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${fmt_LIBRARIES}
    ${imgui_LIBRARIES}
    ${OpenCV_LIBRARIES}
    ${SFML_LIBRARIES}
    ${ImGui-SFML_LIBRARIES}
)

message(STATUS "
Libs:
imgui_LIBRARIES ${imgui_LIBRARIES}
SFML_LIBRARIES ${SFML_LIBRARIES}
OpenCV_LIBRARIES} ${OpenCV_LIBRARIES}
ImGui-SFML_LIBRARIES ${ImGui-SFML_LIBRARIES}
Incs:
imgui_INCLUDES ${imgui_INCLUDES}
SFML_INCLUDES ${SFML_INCLUDES}
OpenCV_INCLUDES ${OpenCV_INCLUDES}
ImGui-SFML_INCLUDES ${ImGui-SFML_INCLUDES}
")

## Copy resources
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/share DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
