cmake_minimum_required(VERSION 4.2)

project(file_explorer
  VERSION "1.0.0"
  DESCRIPTION "File explorer dialog"
  LANGUAGES CXX
)

add_executable(${PROJECT_NAME} main.cpp)


## Find third-party packages
find_package(fmt REQUIRED)
find_package(ImGui-SFML REQUIRED)
find_package(portable-file-dialogs REQUIRED)


## Target
target_link_libraries(${PROJECT_NAME}
  PRIVATE ${fmt_LIBRARIES}
  PRIVATE ${ImGui-SFML_LIBRARIES}
  PRIVATE ${portable-file-dialogs_LIBRARIES}
)

target_include_directories(${PROJECT_NAME}
  PRIVATE include
  PRIVATE ${portable-file-dialogs_INCLUDE_DIRS}
  PRIVATE ${ImGui-SFML_INCLUDE_DIRS}
  PRIVATE ${fmt-SFML_INCLUDE_DIRS}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
