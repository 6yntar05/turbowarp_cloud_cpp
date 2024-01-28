cmake_minimum_required(VERSION 3.15)
project(turbowarp_cloud_cpp CXX)



add_executable(turbowarp_cloud_cpp src/turbowarp_cloud_cpp.cpp src/main.cpp)



install(TARGETS turbowarp_cloud_cpp DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
