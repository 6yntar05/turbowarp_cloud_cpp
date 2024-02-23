#pragma once

#include <memory>
#include <string>

#include "session/turbowarp/result.hpp"

namespace turbowarp {
struct JsonParser {
    static Result<std::string> analize_data(std::string data);
    static std::string error_message(std::string name, int status);
};
}  // namespace turbowarp