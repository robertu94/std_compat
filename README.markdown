# LibStdCompat

LibStdCompat is a set of compatibility headers for C++ 14, 17, and 20 for C++11.  It aims to be lighter weight and more narrowly tailored than some other alternatives such as Boost or replacing your standard library with libcxx when certain fewer features are needed.

LibStdCompat is not complete -- that is it does not implement all C++14, 17, or 20 library features.  But overtime, more and more of the library will be implemented.

## Using LibStdCompat

Simply compile and link to `std_compat`

Generally headers have the same name as their standard library equivalent with a `.h` appended.  I.E. `<memory>` becomes `<memory.h>`, and the structure is put into the `compat::` namespace so `std::make_unique` becomes `compat::make_unique`.

## Dependencies

LibStdCompat depends on:

+ `cmake` version `3.13` or later (3.14 required for python bindings)
+ `pkg-config` version `1.6.3` or later
+ either:
  + `gcc-4.8.5` or later
  + `clang-7.0.0` or later using either `libc++` or `libstdc++`.  Beware that system libraries may need to be recompiled with `libc++` if using `libc++`

LibStdCompat optionally depends on:

+ `Boost` for the implementations of `std::optional` and `std::variant`  when C++17 is not available

## Installing LibPressio using Spack


```
git clone https://github.com/robertu94/spack_packages robertu94_packages
spack repo add robertu94_packages
spack install libstdcompat
```

## Configuring LibStdCompat Manually

LibStdCompat uses cmake to configure build options.  See CMake documentation to see how to configure options

+ `CMAKE_INSTALL_PREFIX` - install the library to a local directory prefix
+ `BUILD_DOCS` - build the project documentation
+ `BUILD_TESTING` - build the test cases

## Building and Installing LibStdCompat

To build and tests and install the library only.

```bash
BUILD_DIR=build
mkdir $BUILD_DIR
cd $BUILD_DIR
cmake ..
make
make test
make install
```

To build the documentation:


```bash
BUILD_DIR=build
mkdir $BUILD_DIR
cd $BUILD_DIR
cmake .. -DBUILD_DOCS=ON
make docs
# the html docs can be found in $BUILD_DIR/html/index.html
# the man pages can be found in $BUILD_DIR/man/
```

