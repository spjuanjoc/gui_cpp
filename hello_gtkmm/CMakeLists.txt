cmake_minimum_required(VERSION 3.19)
project(hello_gtkmm VERSION 0.0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

## Setup Conan
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
      "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP NO_OUTPUT_DIRS
#  BUILD missing
)


## Find third-party packages
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})
find_package(fmt REQUIRED)
find_package(gtk REQUIRED COMPONENTS gtk gtkmm glibmm pango)
#find_package(sigc++ REQUIRED)

## Target
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt gtk::gtk)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${gtk_INCLUDES}
    /usr/lib/x86_64-linux-gnu/
    /usr/lib/x86_64-linux-gnu/glibmm-2.4/include/
    /usr/lib/x86_64-linux-gnu/giomm-2.4/include/
    /usr/lib/x86_64-linux-gnu/gtkmm-3.0/include/
    /usr/lib/x86_64-linux-gnu/sigc++-2.0/include/
    /usr/lib/x86_64-linux-gnu/pangomm-1.4/include/
    /usr/lib/x86_64-linux-gnu/gdkmm-3.0/include/
    /usr/include
    /usr/include/glibmm-2.4/
    /usr/include/pangomm-1.4/
    /usr/include/cairomm-1.0/
    /usr/include/atkmm-1.6/
    /usr/include/gtkmm-3.0
    /usr/include/gdkmm-3.0
    /usr/include/giomm-2.4
    /usr/include/sigc++-2.0
)

#message(STATUS "gtk_INCLUDES ${gtk_INCLUDES}")
