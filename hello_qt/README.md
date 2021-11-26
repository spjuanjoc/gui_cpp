# Hello Qt

This is a "Hello World" for Qt6

## Uses

- CMake
- std 17
- conan
- gcc8 for Qt version 6

## Install

Requires `gcc-8` or greater

The Conan profile must have the compiler.version >= 8

```shell
$ conan profile show Gcc8
Configuration for profile Gcc8:

[settings]
os=Linux
os_build=Linux
arch=x86_64
arch_build=x86_64
compiler=gcc
compiler.version=8
compiler.libcxx=libstdc++11
build_type=Debug
[options]
[build_requires]
[env]
```


```shell
mkdir build && cd build
conan install .. --build=missing --profile=Gcc8
cmake -DCMAKE_MODULE_PATH=$PWD -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```


## Dependencies

If already exist, remove from ~/.conan/data the following packages:

- libjpeg
- bzip2
- libiconv
- zlib
- libpng
- freetype
- pkgconf
- libuuid
- xorg
- libffi
- pcre pcre2
- libelf
- libselinux
- glib
- qt

## See 

[Hello Qt](https://doc.qt.io/archives/3.3/tutorial1-01.html)
