[![Build Status](https://travis-ci.org/XEverentX/Dirichlet_task_by_gradient.svg?branch=master)](https://travis-ci.org/XEverentX/Dirichlet_task_by_gradient)

## Dirichlet task solving by conjugate gradients

### Setup
To work with this repo you need to install:
 - CMake
 - g++(Linux) or vsc(Windows)
 - QT
 - Boost library
 
To setup it on linux use:
```bash
 sudo apt install g++
 sudo apt install cmake
 sudo apt update
 sudo apt install qt5-default
 sudo apt-get install libboost-all-dev
```

### Build & Run
To build application simply follow a few steps:

```bash
mkdir build
cd build
cmake ..
cmake --build . --config RELEASE
```

Use `app` as `<excecutable>`.

To run under `linux` use:

```bash
./<executable>
```

To run under `windows` use:

```bash
.\application\Release\<executable>.exe
```