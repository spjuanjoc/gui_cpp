# Hello Gtk4

This is a "Hello World" example of a GUI using Gtk version 4.
Gtk is Linux only.

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

[Gtk hello world](https://www.gtk.org/docs/getting-started/hello-world)
