# turbowarp_cloud_cpp
The turbowarp data server in C++

## Features
There are none for yet

## Dependencies
- `websocketpp`
- `boost::asio`

## Building
- `git clone --recursive https://github.com/6yntar05/turbowarp_cloud_cpp`
- `cd turbowarp_cloud_cpp`
- `mkdir build && cd build`
- `cmake .. && cmake --build . -j$(nproc)`
- and run server help page: `./server --help`

## Design
Proto description presented in `protocol.md`<br>
Architech presented in \<TODO\>