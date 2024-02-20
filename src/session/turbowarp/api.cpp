#include <iostream>

#include "session/turbowarp/api.hpp"

using namespace turbowarp;

std::string api::analize_data(std::string data) {
    boost::system::error_code ec;
    boost::json::value value = boost::json::parse(data, ec);

    if (ec) {
        return "error: " + ec.message();
    }

    std::cout << value << std::endl;
    return data;
}