//
// Created by john on 08/05/2021.
//

#include "listener.hpp"

//! stl
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

//! boost
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>

//! local
#include "request.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace ott
{
    namespace http
    {
        // Report a failure

        listener::listener(net::io_context &ioc, tcp::endpoint endpoint) : ioc_(ioc), acceptor_(net::make_strand(ioc))
        {
            beast::error_code ec;

            // Open the acceptor
            acceptor_.open(endpoint.protocol(), ec);
            if(ec)
            {
                fail(ec, "open");
                return;
            }

            // Allow address reuse
            acceptor_.set_option(net::socket_base::reuse_address(true), ec);
            if(ec)
            {
                fail(ec, "set_option");
                return;
            }

            // Bind to the server address
            acceptor_.bind(endpoint, ec);
            if(ec)
            {
                fail(ec, "bind");
                return;
            }

            // Start listening for connections
            acceptor_.listen(
                    net::socket_base::max_listen_connections, ec);
            if(ec)
            {
                fail(ec, "listen");
                return;
            }
        }
        // Start accepting incoming connections
        void listener::run()
        {
            std::cout << "start listener::run() " << std::endl;
            do_accept();
            std::cout << "end listener::run() " << std::endl;
        }
        void listener::do_accept()
        {
            std::cout << "start listener::do_accept() " << std::endl;
            // The new connection gets its own strand
            acceptor_.async_accept(
                    net::make_strand(ioc_),
                    beast::bind_front_handler(
                            &listener::on_accept,
                            shared_from_this()));
            std::cout << "end listener::do_accept() " << std::endl;
        }
        void listener::on_accept(beast::error_code ec, tcp::socket socket)
        {
            std::cout << "start listener::on_accept() " << std::endl;
            if(ec)
            {
                fail(ec, "accept");
            }
            else
            {
                // Create the session and run it
                std::make_shared<HttpSession>(
                        std::move(socket))->run();
            }
            // Accept another connection
            do_accept();
            std::cout << "end listener::on_accept() " << std::endl;
        }
    }
}