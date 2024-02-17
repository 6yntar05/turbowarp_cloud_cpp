# turbowarp_cloud_cpp
The turbowarp data server in C++ <br>
[![LLVM/clang(Linux)](https://github.com/6yntar05/turbowarp_cloud_cpp/actions/workflows/conan-fast-check.yml/badge.svg)](https://github.com/6yntar05/turbowarp_cloud_cpp/actions/workflows/conan-fast-check.yml) <br>
[![MSVC(Win32)+GCC(Linux)](https://github.com/6yntar05/turbowarp_cloud_cpp/actions/workflows/conan-multi-platform.yml/badge.svg)](https://github.com/6yntar05/turbowarp_cloud_cpp/actions/workflows/conan-multi-platform.yml)

## Features
There are none for yet

## Dependencies
- For build: conan>=2, cmake>=3.15

## Building
- `git clone --recursive https://github.com/6yntar05/turbowarp_cloud_cpp`
- `cd turbowarp_cloud_cpp`
- `mkdir build && cd build`
- `conan install .. -vvv --build=missing --settings=build_type=Debug --settings compiler.cppstd=20`
- `conan build -vvv --build=missing --settings=build_type=Debug --settings compiler.cppstd=20 ..`
- and run server help page: `./Debug/turbowarp_cloud_cpp --help`

## Design
Proto description presented in `protocol.md`<br>
Architech presented in \<TODO\>