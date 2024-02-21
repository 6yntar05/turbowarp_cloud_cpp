#pragma once

#include <boost/json.hpp>
#include <string>

namespace turbowarp {
    class api {
        public:
            static std::string analize_data(std::string data);
        private:
            static std::string error_message(std::string name, int status);
    };
} // namespace turbowarp_api