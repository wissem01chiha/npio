<!-- omit in toc -->
# NPIO

[![Ubuntu](https://github.com/wissem01chiha/npio/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/wissem01chiha/npio/actions/workflows/ubuntu.yml)
[![Build status](https://ci.appveyor.com/api/projects/status/d44jk17qd31j70qg?svg=true)](https://ci.appveyor.com/project/wissem01chiha/npio)
[![CodeQL](https://github.com/wissem01chiha/npio/actions/workflows/codeql.yml/badge.svg)](https://github.com/wissem01chiha/npio/actions/workflows/codeql.yml)
![GitHub License](https://img.shields.io/github/license/wissem01chiha/npio)
[![CodeFactor](https://www.codefactor.io/repository/github/wissem01chiha/npio/badge)](https://www.codefactor.io/repository/github/wissem01chiha/npio)

- [1.0 Installation](#10-installation)
  - [1.1 Binary Release](#11-binary-release)
  - [1.2 Build from Source](#12-build-from-source)
    - [1.2.1 CMake](#121-cmake)
  - [1.2.2 Menson](#122-menson)
  - [1.2.3 Bazel](#123-bazel)
- [2.0 Testing](#20-testing)
  - [2.1 CMake](#21-cmake)
  - [2.2 Meson](#22-meson)
  - [2.3 Bazel](#23-bazel)
- [3.0 Documenation](#30-documenation)
  - [3.1 Generate documenation](#31-generate-documenation)
- [4.0 License](#40-license)

`npio` is a C99 version of [cnpy](https://github.com/rogersce/cnpy), written by [Carl Rogers](https://github.com/rogersce). It is a library for reading and writing [NumPy](https://numpy.org/doc/stable/reference/generated/numpy.lib.format.html) `.npy` and `.npz` files, which is no longer actively maintained.

NumPy provides the `save` method for saving arrays into `.npy` files and `savez` for zipping multiple `.npy` arrays together into a `.npz` file.  

`npio` allows you to read and write these formats in C99.  

Please feel free to open an issue. I will try to address any concerns as best I can.

# 1.0 Installation

## 1.1 Binary Release

## 1.2 Build from Source

### 1.2.1 CMake 

[CMake](https://cmake.org) 3.24 or higher is required.  

The default installation directory is `/usr/local`.  
To specify a different directory, add `-DCMAKE_INSTALL_PREFIX=/path/to/install/dir` to the CMake invocation in step 4.

1. Clone the repository:
  ```shell
   git clone https://github.com/wissem01chiha/npio
  ```
2. - Configure the build: 
  ```shell
  cmake -B build -DCMAKE_INSTALL_PREFIX=~/build/install
  ```
3. - Build and install:
  ```shell
  ninja install
  ```

## 1.2.2 Menson 

Meson >= 1.10.0 is required. For more information, refer to [Quick-guide](https://mesonbuild.com/Quick-guide.html) 

  ```shell
  meson setup builddir 
  cd builddir 
  meson compile 
  ```

Then install the library using: 

  ```shell
  meson install
  ```

## 1.2.3 Bazel 

> [NOTE] Note: Bazel is not yet supported. Please use [cmake](#11-cmake) or [meson](#12-menson) instead.


# 2.0 Testing

## 2.1 CMake 

## 2.2 Meson 

To run project tests:

```shell
meson test 
```

## 2.3 Bazel 

> [NOTE] Note: Bazel tests are not yet supported. Use [cmake](#11-cmake) or [meson](#12-menson) to run tests


# 3.0 Documenation 

All API documentation can be found [here]()

## 3.1 Generate documenation

npio uses [Sphinx]() alongside [Doxygen]() to generate documentation.


# 4.0 License 

All material is provided under MIT License unless otherwise specified.

see the [LICENSE](LICENSE) file for more details

