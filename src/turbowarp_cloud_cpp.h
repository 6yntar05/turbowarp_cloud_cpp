#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define TURBOWARP_CLOUD_CPP_EXPORT __declspec(dllexport)
#else
  #define TURBOWARP_CLOUD_CPP_EXPORT
#endif

TURBOWARP_CLOUD_CPP_EXPORT void turbowarp_cloud_cpp();
TURBOWARP_CLOUD_CPP_EXPORT void turbowarp_cloud_cpp_print_vector(const std::vector<std::string> &strings);
