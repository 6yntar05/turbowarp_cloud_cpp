#include "session/turbowarp/json_parser.hpp"

#include <boost/json.hpp>
#include <string>

#include "session/turbowarp/methods.hpp"

using namespace turbowarp;

Result<std::string> JsonParser::analize_data(std::string data) {
    boost::system::error_code ec;
    auto json = boost::json::parse(data, ec);

    if (ec) {
        return Error<std::string>(JsonParser::error_message("Must be json", 4000));
    }

    return method::value_to_method(json);
}

std::string JsonParser::error_message(std::string name, int status) {
    boost::json::value e = {{"error", name}, {"status", status}};

    return boost::json::serialize(e);
}