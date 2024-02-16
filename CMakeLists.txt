cmake_minimum_required(VERSION 3.15)
project(turbowarp_cloud_cpp CXX)

# Properties
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter -fdiagnostics-color=always -O3")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter -fcolor-diagnostics -O3")
endif ()
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# todo: do it properly
if (MSVC)
    add_compile_options(/bigobj)
endif ()

# Sources
file (GLOB_RECURSE SRCFILES "./src/*.cpp")
add_executable (turbowarp_cloud_cpp ${SRCFILES})
include_directories (AFTER SYSTEM ./src)

# Dependencies
find_package (Boost REQUIRED)
find_package (libpqxx REQUIRED)
find_package (OpenSSL REQUIRED)
target_include_directories (turbowarp_cloud_cpp PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${CONAN_INCLUDE_DIRS}
        ${libpqxx_INCLUDE_DIRS}
        Boost::boost)
target_link_libraries (turbowarp_cloud_cpp PRIVATE
        ${Boost_LIBRARIES}
        ${CONAN_LIBS}
        ${libpqxx_LIBRARIES}
        Boost::boost
        PostgreSQL::PostgreSQL
        libpq::pq
        libpq::pgcommon
        libpq::pgport
        libpqxx::pqxx
        OpenSSL::SSL)

# Targets
install (TARGETS turbowarp_cloud_cpp DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
