#include "turbowarp_cloud_cpp.h"
#include <vector>
#include <string>

int main() {
    turbowarp_cloud_cpp();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    turbowarp_cloud_cpp_print_vector(vec);
}
