#include <iostream>

#include "session/turbowarp/api.hpp"

using namespace turbowarp;

std::string api::analize_data(std::string data) {
    boost::system::error_code ec;
    auto value = boost::json::parse(data, ec);

    if (ec) {
        return api::error_message(ec.message(), 4000);
    }

    std::cout << value.at("method") << std::endl;

    std::cout << value << std::endl;

    return data;
}

std::string api::error_message(std::string name, int status) {
    boost::json::value e = {
        {"error", name},
        {"status", status}
    };

    return boost::json::serialize(e);
}