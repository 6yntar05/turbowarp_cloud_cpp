#include "session/turbowarp/methods.hpp"

#include "session/turbowarp/json_parser.hpp"

using namespace turbowarp::method;

BaseMethod::BaseMethod(std::vector<std::string> const &params) { this->params = params; }

BaseMethod::BaseMethod(const BaseMethod &method) { this->params = method.params; }

void AvailableMethods::base_init() {
    AvailableMethods::methods = {
        {"handshake", std::make_shared<method::Handshake>()},
        {"set", std::make_shared<method::Set>()},
        {"create", std::make_shared<method::Create>()},
        {"rename", std::make_shared<method::Rename>()},
        {"delete", std::make_shared<method::Delete>()},
    };
}

bool turbowarp::method::is_valid(std::vector<std::string> const &params,
                                 boost::json::value const &value) {
    try {
        for (auto p : params) {
            boost::json::value_to<std::string>(value.at(p));
        }
    } catch (...) {
        return false;
    }

    return true;
}

turbowarp::Result<std::string> turbowarp::method::value_to_method(boost::json::value const &value) {
    try {
        std::string method_name = boost::json::value_to<std::string>(value.at("method"));
        auto method = find_method(method_name);
        if (is_valid(method->params, value)) {
            return method->custom_behavior(value);
        }
    } catch (...) {
    }

    return Error<std::string>(turbowarp::JsonParser::error_message("Generic Error", 4000));
}

std::shared_ptr<BaseMethod> turbowarp::method::find_method(std::string const &method) {
    return turbowarp::method::AvailableMethods::methods.at(method);
}