cmake_minimum_required(VERSION 3.20)

project(hello_imgui2
  VERSION "1.0.0"
  DESCRIPTION "Hello ImGui with conan"
  LANGUAGES CXX
)

add_executable(${PROJECT_NAME} main.cpp)


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


## Target
target_link_libraries(${PROJECT_NAME} PRIVATE ${fmt_LIBRARIES} ${imgui_LIBRARIES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
