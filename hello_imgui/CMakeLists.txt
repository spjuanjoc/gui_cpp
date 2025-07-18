cmake_minimum_required(VERSION 3.24)

project(hello_imgui
  VERSION "1.0.0"
  DESCRIPTION "Hello ImGui with conan"
  LANGUAGES CXX
)

add_executable(${PROJECT_NAME} main.cpp)


## Find third-party packages
find_package(fmt REQUIRED)
find_package(imgui REQUIRED)


## Target
target_link_libraries(${PROJECT_NAME} PRIVATE ${fmt_LIBRARIES} ${imgui_LIBRARIES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
