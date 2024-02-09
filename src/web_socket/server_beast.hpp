#ifndef server_beast_hpp
#define server_beast_hpp

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <sstream>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = boost::beast::http;    // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>

using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace web_socket {
    // Report a failure
    void fail(beast::error_code ec, char const* what);

    // Echoes back all received WebSocket messages
    class session : public std::enable_shared_from_this<session> {
        websocket::stream<beast::tcp_stream> ws_;
        beast::flat_buffer buffer_;

        public:
            // Take ownership of the socket
            explicit session(tcp::socket&& socket) : ws_(std::move(socket)) {}

            // Start the asynchronous operation
            void run();
            void on_accept(beast::error_code ec);
            void do_read();
            void on_read(beast::error_code ec, std::size_t bytes_transferred);
            void on_write(beast::error_code ec, std::size_t bytes_transferred);
    };

    //------------------------------------------------------------------------------

    // Accepts incoming connections and launches the sessions
    class listener : public std::enable_shared_from_this<listener> {
        net::io_context& ioc_;
        tcp::acceptor acceptor_;

        public:
            listener(net::io_context& ioc, tcp::endpoint endpoint);

            // Start accepting incoming connections
            void run();

        private:
            void do_accept();
            void on_accept(beast::error_code ec, tcp::socket socket);
    };
}

#endif // !server_beast_hpp
