#ifndef STANDART_HEADERS_HPP
#define STANDART_HEADERS_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>
#include <memory>
#include <utility>
#include <boost/beast/websocket/ssl.hpp>

#include "handler.hpp"

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace ssl = boost::asio::ssl;
using tcp = asio::ip::tcp;

using std::shared_ptr;
using std::make_shared;
using std::enable_shared_from_this;

#endif //STANDART_HEADERS_HPP
