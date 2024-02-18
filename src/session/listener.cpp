#include "session/listener.hpp"

namespace session {

listener::listener(asio::io_context &ioc, const tcp::endpoint &endpoint,
                   listener::handlers handlers)
    : ioc_(ioc), endpoint_(endpoint), acceptor_(ioc, endpoint), handlers_(std::move(handlers)) {}

void listener::start() {
    if (!acceptor_.is_open()) {
        acceptor_.open(endpoint_.protocol());
    }

    do_accept();
}

void listener::stop() {
    if (acceptor_.is_open()) {
        acceptor_.close();
    }
}

void listener::do_accept() {
    acceptor_.async_accept(
        [self = shared_from_this()](const beast::error_code &ec, tcp::socket socket) {
            if (ec == asio::error::operation_aborted) {
                // when listener.stop()
                return;
            }
            handlers::context context{self};

            if (ec) {
                self->handlers_.on_accept.failure(context, ec);
                return;
            }

            self->handlers_.on_accept.success(context, std::move(socket));

            self->do_accept();
        });
}

}  // namespace session