#pragma once

#include <boost/json.hpp>
#include <map>
#include <string>

#include "session/turbowarp/json_parser.hpp"
#include "session/turbowarp/result.hpp"

namespace turbowarp {
namespace method {
struct BaseMethod {
    std::vector<std::string> params;

    BaseMethod(std::vector<std::string> const &params);
    BaseMethod(BaseMethod const &method);

    virtual Result<std::string> custom_behavior(boost::json::value const &value) = 0;
};

struct AvailableMethods {
    static inline std::map<std::string, std::shared_ptr<BaseMethod>> methods;

    static void base_init();
};

struct Handshake : BaseMethod {
    Handshake() : BaseMethod({"method", "project_id", "user"}) {}

    Result<std::string> custom_behavior(boost::json::value const &value);
};

struct Set : BaseMethod {
    Set() : BaseMethod({"method", "name", "value"}) {}

    Result<std::string> custom_behavior(boost::json::value const &value);
};

struct Create : BaseMethod {
    Create() : BaseMethod({"method", "name", "value"}) {}

    Result<std::string> custom_behavior(boost::json::value const &value);
};

struct Rename : BaseMethod {
    Rename() : BaseMethod({"method", "name", "new_name"}) {}

    Result<std::string> custom_behavior(boost::json::value const &value);
};

struct Delete : BaseMethod {
    Delete() : BaseMethod({"method", "name"}) {}

    Result<std::string> custom_behavior(boost::json::value const &value);
};

bool is_valid(std::vector<std::string> const &params, boost::json::value const &value);
std::shared_ptr<BaseMethod> find_method(std::string const &method);
Result<std::string> value_to_method(boost::json::value const &value);
}  // namespace method
}  // namespace turbowarp