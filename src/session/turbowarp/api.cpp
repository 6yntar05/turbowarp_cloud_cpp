#include <iostream>

#include "session/turbowarp/api.hpp"

using namespace turbowarp;

std::string JsonParser::ok_message = R"({"status": "ok"})";

method::Params method::Handshake::params = {{"method", "project_id", "user"}};
method::Params method::Set::params = {{"method", "name", "value"}};
method::Params method::Create::params = {{"method", "name", "value"}};
method::Params method::Rename::params = {{"method", "name", "new_name"}};
method::Params method::Delete::params = {{"method", "name"}};

std::string JsonParser::analize_data(std::string data) {
    boost::system::error_code ec;
    auto json = boost::json::parse(data, ec);

    if (ec) {
        return JsonParser::error_message("Must be json", 4000);
    }

    std::string method;

    try {
        method = boost::json::value_to<std::string>(json.at("method"));
    } catch(...) {
        return JsonParser::error_message("Generic Error", 4000);
    }

    if (method == "handshake") {
        if (method::is_valid(method::Handshake::params, json)) {
            auto handshake = method::Handshake(json);
            std::cout << handshake.values.at("method") << handshake.values.at("project_id") << handshake.values.at("user") << std::endl;
        }
    }

    if (method == "set") {
        if (method::is_valid(method::Set::params, json)) {
            auto handshake = method::Set(json);
            std::cout << handshake.values.at("method") << handshake.values.at("name") << handshake.values.at("value") << std::endl;
        }
    }

    if (method == "create") {
        if (method::is_valid(method::Create::params, json)) {
            auto handshake = method::Create(json);
            std::cout << handshake.values.at("method") << handshake.values.at("name") << handshake.values.at("value") << std::endl;
        }
    }

    if (method == "rename") {
        if (method::is_valid(method::Rename::params, json)) {
            auto handshake = method::Rename(json);
            std::cout << handshake.values.at("method") << handshake.values.at("name") << handshake.values.at("new_name") << std::endl;
        }
    }

    if (method == "delete") {
        if (method::is_valid(method::Delete::params, json)) {
            auto handshake = method::Delete(json);
            std::cout << handshake.values.at("method") << handshake.values.at("name") << std::endl;
        }
    }

    return JsonParser::ok_message;
}

std::string JsonParser::error_message(std::string name, int status) {
    boost::json::value e = {
        {"error", name},
        {"status", status}
    };

    return boost::json::serialize(e);
}