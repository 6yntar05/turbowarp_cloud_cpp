cmake_minimum_required(VERSION 3.15)
project(turbowarp_cloud_cpp CXX)

# Properties
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter -fdiagnostics-color=always")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter -fcolor-diagnostics")
endif ()
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Sources
file (GLOB_RECURSE SRCFILES "./src/*.cpp")
add_executable (turbowarp_cloud_cpp ${SRCFILES})
include_directories (AFTER SYSTEM ./src)

# Dependencies
find_package (Boost REQUIRED)
find_package (websocketpp REQUIRED)
find_package (libpqxx REQUIRED)
target_include_directories (turbowarp_cloud_cpp PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${WEBSOCKETPP_INCLUDE_DIRS}
        ${CONAN_INCLUDE_DIRS}
        websocketpp::websocketpp
        Boost::boost
        libpqxx)
target_link_libraries (turbowarp_cloud_cpp PRIVATE
        ${Boost_LIBRARIES}
        ${WEBSOCKETPP_LIBRARIES}
        ${CONAN_LIBS}
        websocketpp::websocketpp
        Boost::boost
        PostgreSQL::PostgreSQL
        libpqxx::pqxx)

# Targets
install (TARGETS turbowarp_cloud_cpp DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
