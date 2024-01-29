cmake_minimum_required(VERSION 3.15)
project(turbowarp_cloud_cpp CXX)

# Properties
set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Sources
add_executable(turbowarp_cloud_cpp src/CONAN_BUILD_TEST.cpp src/main.cpp)

# Dependencies
find_package(Boost REQUIRED COMPONENTS system)
find_package(websocketpp REQUIRED)
target_include_directories(turbowarp_cloud_cpp PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${WEBSOCKETPP_INCLUDE_DIRS}
        ${CONAN_INCLUDE_DIRS}
        websocketpp::websocketpp
        boost::boost)
target_link_libraries(turbowarp_cloud_cpp PRIVATE
        ${Boost_LIBRARIES}
        ${WEBSOCKETPP_LIBRARIES}
        ${CONAN_LIBS}
        websocketpp::websocketpp
        boost::boost)

# Targets
install(TARGETS turbowarp_cloud_cpp DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
