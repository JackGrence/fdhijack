# fdhijack tool

app/chfd is the user-space utility by which we can use to exchange two or three processes' fd.  

## Getting Started

script/fdhj_load is a script for loading the kernel module fdhj, and create the corresponding device node /dev/fdhj.
The major number for fdhj is dynamically allocated if not specified on calling fdhj_load with the argument fdhj_major=<major>.

driver/fdhj_<kernel_version> are the kernel modules for operating file objects in kernel.

libfdhj is a library that wraps the fdhj module for user-space applications.

ceh wraps setjmp() and longjmp() to be a try...catch-style error handling framework in C.

### Prerequisites

#### [CMake](https://cmake.org/)

Debian/Ubuntu:

```
sudo apt-get update
sudo apt-get install cmake
```

### Installing

#### Build chfd

```
cmake ./
make
```

If build successfully, chfd in bin folder.

#### Build fdhj.ko

```
cd driver/fdhj_3.10.49
make
```

fdhj_3.10.49 can work on Linux 4.4.98 for me.

### Usage

(After gather chfd, fdhj.ko, fdhj_load in a directory)
```
$ ./fdhj_load [fdhj_major=<major>]
$ ./chfd <pid1> <fd1> <pid2> <fd2> [<pid3> <fd3>]
```
