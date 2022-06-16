# pybind\_scikit\_example

Example repo demonstrating how to combine C++ and python code with using
[`pybind11`](https://github.com/pybind/pybind11). There are a number of
ways to do this; the approach here is to use the `pip` `pybind11` package
(rather than submodules) and `CMake` + `scikit_build` along with the
usual `setuptools` (rather than writing our own `CMakeExtension` in
`setup.py`). The C++ is compiled into a `_cpp` appended python module that
is then imported into the top level module.

There is a really great example of doing this same thing
[here](https://github.com/pybind/scikit_build_example), which heavily
influenced the build system here. I found, however, that certain common
features are missing, and it's not always clear how you'd do them and still
be confident both editable and non-editable installs work. I also like to
organize the code a bit differently.

## Additional Features

1. Splitting up C++ source files and bindings instead of bunching into
  one file
1. Passing 1/2/3D `numpy` arrays and structured arrays to and from C++ code
  using a C-struct definition
1. Including some package data via `MANIFEST.in` and passing the file path
  from python to C++
1. Linking against external code that we have (e.g. in a submodule) by
  including its CMakeLists.txt and linking against its libs
1. Linking against external .h/.so that we don't have the code for, so we
  can't compile it ourselves. But, the resulting package needs to have the
  .so paths embedded in it so it can find them at runtime
1. Including multiple python-bound C++ modules

## Overview

If you're new to `pybind11`, start by examining the setup for the
`bingo_cpp` module. This is a very simple module with just a few things in
it for beginners. If you're looking for the full set of example features,
such as numpy arrays, then check out `pingo_cpp`.

### bingo\_cpp

The code is in `src/bingo_cpp`, the C++/`pybind11` build config is in
`CMakeLists.txt`, and the imports are in
`src/pybind_scikit_example/__init__.py` and `example.py`. There is an
enum and function defined in a namespace, which is good practice, rather
than putting them into the global scope.

`src/bingo_cpp/bindings.cpp` shows a brief example of exposing the enum
and function to python.

### pingo\_cpp

TODO
