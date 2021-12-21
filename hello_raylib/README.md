# Hello Raylib

This is a "Hello World" example of a GUI using raylib version 3.5.

## Requirements

- CMake
- std 11
- conan


## Build

```shell
mkdir build && cd build
conan install .. --build=missing
cmake -DCMAKE_MODULE_PATH=$PWD -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```

## See

[RayLib](https://www.raylib.com/index.html)
