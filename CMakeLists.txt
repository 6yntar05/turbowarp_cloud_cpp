cmake_minimum_required(VERSION 3.15)
project(turbowarp_cloud_cpp CXX)

# Properties
set (CMAKE_CXX_STANDARD 17)
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
find_package (libpqxx REQUIRED)
target_include_directories (turbowarp_cloud_cpp PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${CONAN_INCLUDE_DIRS}
        Boost::boost)
target_link_libraries (turbowarp_cloud_cpp PRIVATE
        ${Boost_LIBRARIES}
        ${CONAN_LIBS}
        Boost::boost
        PostgreSQL::PostgreSQL
        libpqxx::pqxx)

# Targets
install (TARGETS turbowarp_cloud_cpp DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
