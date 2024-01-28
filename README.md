# turbowarp_cloud_cpp
The turbowarp data server in C++

## Features
There are none for yet

## Dependencies
- For build: conan>=2, cmake>=3.15
- `websocketpp`
- `boost::asio`
- \<TODO: Database\>

## Building
- `git clone --recursive https://github.com/6yntar05/turbowarp_cloud_cpp`
- `cd turbowarp_cloud_cpp`
- `mkdir build && cd build`
- `conan install .. --build=missing`
- `conan build ..`
- and run server help page: `./Release/turbowarp_cloud_cpp --help`

## Design
Proto description presented in `protocol.md`<br>
Architech presented in \<TODO\>