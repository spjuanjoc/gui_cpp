cmake_minimum_required(VERSION 3.24)

project(hello_imgui_sfml
  VERSION "1.0.0"
  DESCRIPTION "Hello ImGui+SFML with conan"
  LANGUAGES CXX
)

## Set the project as an executable target # 1
add_executable(${PROJECT_NAME}
  src/bindings/imgui-SFML.cpp
  src/main.cpp
)

## Set the project as an executable target # 2
add_executable(${PROJECT_NAME}_multi
  src/bindings/imgui-SFML.cpp
  src/main2.cpp
)


## Find third-party packages
find_package(fmt REQUIRED)
find_package(imgui REQUIRED)
find_package(SFML REQUIRED)
#find_package(ImGui-SFML REQUIRED)


## Target # 1
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${fmt_LIBRARIES}
    ${imgui_LIBRARIES}
    ${SFML_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

## Target # 2
target_link_libraries(${PROJECT_NAME}_multi
  PRIVATE
  ${fmt_LIBRARIES}
  ${imgui_LIBRARIES}
  ${SFML_LIBRARIES}
)

target_include_directories(${PROJECT_NAME}_multi PRIVATE include)

target_compile_features(${PROJECT_NAME}_multi PRIVATE cxx_std_20)


## Copy resources to the bin directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/share DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
