# Hello Raylib

This is a "Hello World" example of a GUI using raylib version 5.5.

## Requirements

- CMake > 3.24
- conan 2


## Build

```shell
mkdir build && cd build
cmake .. -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=/path/to/conan_provider.cmake -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

## See

[RayLib](https://www.raylib.com/index.html)
