cmake_minimum_required(VERSION 3.20)

project(hello_imgui_opengl
  VERSION "1.0.0"
  DESCRIPTION "Hello ImGui-opengl with conan"
  LANGUAGES CXX
)

add_executable(${PROJECT_NAME}
  bindings/imgui_impl_glfw.cpp
  bindings/imgui_impl_opengl3.cpp
  main.cpp
)


## Setup Conan < 2.0
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD
    "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake"
  )
endif ()


include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_autodetect(settings)
conan_check(REQUIRED)
conan_cmake_run(CONANFILE conanfile.txt
  BASIC_SETUP NO_OUTPUT_DIRS
  BUILD missing
  SETTINGS ${settings}
)

## Find third-party packages
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})
find_package(fmt REQUIRED)
find_package(imgui REQUIRED)
find_package(opengl_system REQUIRED)
find_package(glad REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)


## Target
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${fmt_LIBRARIES}
    ${imgui_LIBRARIES}
    ${glfw_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${glad_LIBRARIES}
#    ${glm_LIBRARIES}
    ${opengl_LIBRARIES}
    glm::glm
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PUBLIC bindings)
target_compile_definitions(${PROJECT_NAME} PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)
