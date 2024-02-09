#include "web_socket/server_beast.hpp"

using namespace web_socket;

void web_socket::fail(beast::error_code ec, char const* what) {
    std::cerr << what << ": " << ec.message() << std::endl;
}

// Start the asynchronous operation
void session::run() {
    // Set suggested timeout settings for the websocket
    ws_.set_option(
        websocket::stream_base::timeout::suggested(
            beast::role_type::server));

    // Set a decorator to change the Server of the handshake
    ws_.set_option(websocket::stream_base::decorator(
        [](websocket::response_type& res) {
            res.set(http::field::server,
                std::string("web Iot server") +
                " 1.0");
        }));
    
    beast::flat_buffer buffer;

    // Read the HTTP request ourselves
    http::request<http::string_body> req;
    http::read(ws_.next_layer(), buffer, req);

    // See if its a WebSocket upgrade request
    if (websocket::is_upgrade(req)) {
        // Construct the stream, transferring ownership of the socket
        //stream<tcp_stream> ws(std::move(sock));

        // Clients SHOULD NOT begin sending WebSocket
        // frames until the server has provided a response.
        BOOST_ASSERT(buffer.size() == 0);

        // Accept the upgrade request
        ws_.async_accept(req,
            beast::bind_front_handler(
                &session::on_accept,
                shared_from_this()));

        std::cout << "new connection: " << req.target() << std::endl;
    }
}

void session::on_accept(beast::error_code ec) {
    if (ec)
        return fail(ec, "accept");

    // Read a message
    do_read();
}
    
void session::do_read() {
    // Read a message into our buffer
    ws_.async_read(
        buffer_,
        beast::bind_front_handler(
            &session::on_read,
            shared_from_this()));
}

void session::on_read(beast::error_code ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    // This indicates that the session was closed
    if (ec == websocket::error::closed) {
        std::cout << "close connection" << std::endl;
        return;
    }

    if (ec)
        fail(ec, "read");

    // Echo the message
    std::stringstream ss; 
    ss << boost::beast::make_printable(buffer_.data());
    std::cout << ss.str() << std::endl;
    ws_.text(ws_.got_text());
    ws_.async_write(
        buffer_.data(),
        beast::bind_front_handler(
            &session::on_write,
            shared_from_this()));
}

void session::on_write(beast::error_code ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (ec)
        return fail(ec, "write");

    // Clear the buffer
    buffer_.consume(buffer_.size());

    // Do another read
    do_read();
}

//------------------------------------------------------------------------------

// Accepts incoming connections and launches the sessions
listener::listener(net::io_context& ioc, tcp::endpoint endpoint) : ioc_(ioc), acceptor_(ioc) {
        beast::error_code ec;

        // Open the acceptor
        acceptor_.open(endpoint.protocol(), ec);
        if (ec) {
            fail(ec, "open");
            return;
        }

        // Allow address reuse
        acceptor_.set_option(net::socket_base::reuse_address(true), ec);
        if (ec) {
            fail(ec, "set_option");
            return;
        }

        // Bind to the server address
        acceptor_.bind(endpoint, ec);
        if (ec) {
            fail(ec, "bind");
            return;
        }

        // Start listening for connections
        acceptor_.listen(net::socket_base::max_listen_connections, ec);
        if (ec) {
            fail(ec, "listen");
            return;
        }
    }

// Start accepting incoming connections
void listener::run() {
    do_accept();
}

void listener::do_accept() {
    // The new connection gets its own strand
    acceptor_.async_accept(
        net::make_strand(ioc_),
        beast::bind_front_handler(
            &listener::on_accept,
            shared_from_this()));
}

void listener::on_accept(beast::error_code ec, tcp::socket socket) {
    if (ec) {
        fail(ec, "accept");
    } else {
        // Create the session and run it
        std::make_shared<session>(std::move(socket))->run();
    }

    // Accept another connection
    do_accept();
}


//------------------------------------------------------------------------------

// int main(int argc, char* argv[]) {
//     auto const address = net::ip::make_address("0.0.0.0");
//     auto const port = 80;
//     auto const threads = 4;
//
//     // The io_context is required for all I/O
//     net::io_context ioc{ threads };
//
//     // Create and launch a listening port
//     std::make_shared<listener>(ioc, tcp::endpoint{ address, 80 })->run();
//
//     // Run the I/O service on the requested number of threads
//     std::vector<std::thread> v;
//     v.reserve(threads - 1);
//     for (auto i = threads - 1; i > 0; --i)
//         v.emplace_back(
//             [&ioc]
//             {
//                 ioc.run();
//             });
//     ioc.run();
//
//     return EXIT_SUCCESS;
// }
