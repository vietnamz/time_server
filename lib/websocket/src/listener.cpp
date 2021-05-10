//
// Created by john on 08/05/2021.
//

#include "listener.hpp"

//! stl
#include <thread>
#include <iostream>
//! boost
#include <boost/asio/ip/tcp.hpp>

//! local
#include "session.hpp"
#include "logging.hpp"


namespace ott
{
    namespace websocket
    {
        listener::listener(net::io_context &ioc, tcp::endpoint endpoint) : ioc_(ioc), acceptor_(ioc)
        {
            beast::error_code ec;

            // Open the acceptor
            acceptor_.open(endpoint.protocol(), ec);
            if(ec)
            {
                ott::util::fail(ec, "open");
                return;
            }

            // Allow address reuse
            acceptor_.set_option(net::socket_base::reuse_address(true), ec);
            if(ec)
            {
                ott::util::fail(ec, "set_option");
                return;
            }

            // Bind to the server address
            acceptor_.bind(endpoint, ec);
            if(ec)
            {
                ott::util::fail(ec, "bind");
                return;
            }

            // Start listening for connections
            acceptor_.listen(
                    net::socket_base::max_listen_connections, ec);
            if(ec)
            {
                ott::util::fail(ec, "listen");
                return;
            }
        }
        void listener::run() {
            std::cout << "First listener is started on " << std::this_thread::get_id() << std::endl;
            do_accept();
        }

        void listener::on_accept(beast::error_code ec, tcp::socket socket) {
            std::cout << "start on_accept on " << std::this_thread::get_id() << std::endl;
            if(ec)
            {
                ott::util::fail(ec, "accept");
            }
            else
            {
                // Create the session and run it
                std::make_shared<session>(std::move(socket))->run();
            }
            std::cout << "end on_accept on " << std::this_thread::get_id() << std::endl;

            // Accept another connection
            do_accept();

        }

        void listener::do_accept() {
            std::cout << "commit a new accept handler on " << std::this_thread::get_id() << std::endl;
            // The new connection gets its own strand
            acceptor_.async_accept(
                    net::make_strand(ioc_),
                    beast::bind_front_handler(
                            &listener::on_accept,
                            shared_from_this()));
        }
    }
}