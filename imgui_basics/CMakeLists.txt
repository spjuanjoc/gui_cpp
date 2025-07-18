cmake_minimum_required(VERSION 3.24)

project(imgui_basics VERSION "1.0.0" LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)


## Find third-party packages
find_package(fmt REQUIRED)
find_package(ImGui-SFML REQUIRED)


## Target
target_link_libraries(${PROJECT_NAME} PRIVATE ${ImGui-SFML_LIBRARIES} ${fmt_LIBRARIES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
#target_include_directories(${PROJECT_NAME} PRIVATE ${imgui_INCLUDES})

#message(STATUS "imgui_INCLUDES ${imgui_INCLUDES}")

## Copy resources
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/share DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
