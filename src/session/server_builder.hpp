#pragma once

#include "session/handler.hpp"
#include "session/listener.hpp"
#include "session/server.hpp"
#include "session/session.hpp"
#include "session/standard_headers.hpp"

namespace session {

void configure_ssl(ssl::context &ctx, const std::string& chain_file, const std::string& privkey_file) {
    ctx.set_options(boost::asio::ssl::context::default_workarounds |
                    boost::asio::ssl::context::no_sslv2 |
                    boost::asio::ssl::context::single_dh_use);

    ctx.use_certificate_chain_file(chain_file);

    ctx.use_private_key_file(privkey_file, boost::asio::ssl::context::file_format::pem);
}

server::server_ptr build_server(boost::asio::io_context &io_context,
                                const asio::ip::tcp::endpoint endpoint,
                                const std::string& chain_file,
                                const std::string& privkey_file) {
    using namespace session;

    boost::asio::ssl::context ctx{boost::asio::ssl::context::tlsv13};
    configure_ssl(ctx, std::move(chain_file), std::move(privkey_file));

    return std::make_shared<server>(server::config_t{
        .endpoint = endpoint,
        .io_context = io_context,
        .ssl_context = std::move(ctx),
    });
}

}  // namespace session
