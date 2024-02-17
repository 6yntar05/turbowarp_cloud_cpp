#pragma once

#include <spdlog/spdlog.h>

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <memory>
#include <utility>

#include "session/handler.hpp"

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace ssl = boost::asio::ssl;
using tcp = asio::ip::tcp;

using std::enable_shared_from_this;
using std::make_shared;
using std::shared_ptr;
