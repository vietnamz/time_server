//
// Created by john on 09/05/2021.
//

#include "session.hpp"

#include <thread>
#include <iostream>

#include "logging.hpp"
#include "timer.hpp"

namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>

namespace ott
{
    namespace websocket
    {
        session::session(tcp::socket &&socket) : ws_(std::move(socket)){}
        void session::run() {
            // We need to be executing within a strand to perform async operations
            // on the I/O objects in this session. Although not strictly necessary
            // for single-threaded contexts, this example code is written to be
            // thread-safe by default.
            std::cout << "First session is running on " << std::this_thread::get_id() << std::endl;
            net::dispatch(ws_.get_executor(),
                          beast::bind_front_handler(
                                  &session::on_run,
                                  shared_from_this()));
        }
        void session::on_run()
        {
            std::cout << "start session on_run " << std::this_thread::get_id() << std::endl;
            // Set suggested timeout settings for the websocket
            ws_.set_option(
                    beast::websocket::stream_base::timeout::suggested(
                            beast::role_type::server));

            // Set a decorator to change the Server of the handshake
            ws_.set_option(beast::websocket::stream_base::decorator(
                    [](beast::websocket::response_type& res)
                    {
                        res.set(http::field::server,
                                std::string(BOOST_BEAST_VERSION_STRING) +
                                " websocket-server-async");
                    }));
            // Accept the websocket handshake
            ws_.async_accept(
                    beast::bind_front_handler(
                            &session::on_accept,
                            shared_from_this()));
            std::cout << "end session on_run " << std::this_thread::get_id() << std::endl;
            //! start timer corouting

        }
        session::~session() {
            std::cout << "session destructor\n";
        }
        void session::do_schedule()
        {
            std::cout << "start session on_schedule " << std::this_thread::get_id() << std::endl;
            timer t = make_timer();
            time_ = t.get();
            //do_read();
            ws_.text(ws_.got_text());
            ws_.async_write(
                    boost::asio::buffer(time_),
                    beast::bind_front_handler(
                            &session::on_write,
                            shared_from_this()));

        }
        void session::on_accept(beast::error_code ec) {
            std::cout << "start session on_accept " << std::this_thread::get_id() << std::endl;
            if(ec)
                return ott::util::fail(ec, "accept");

            // Read a message
            do_schedule();
            std::cout << "end session on_accept " << std::this_thread::get_id() << std::endl;
        }

        void session::do_read() {
            std::cout << "start session do_read " << std::this_thread::get_id() << std::endl;
            // Read a message into our buffer
            ws_.async_read(
                    buffer_,
                    beast::bind_front_handler(
                            &session::on_read,
                            shared_from_this()));
            std::cout << "end session do_read " << std::this_thread::get_id() << std::endl;
        }

        void session::on_read(beast::error_code ec, std::size_t bytes_transferred) {
            boost::ignore_unused(bytes_transferred);
            std::cout << "start session on_read on " << std::this_thread::get_id() << std::endl;
            // This indicates that the session was closed
            if(ec == beast::websocket::error::closed)
                return;

            if(ec)
                ott::util::fail(ec, "read");

            // do nothing for now.
        }
        void session::on_write(beast::error_code ec, std::size_t bytes_transferred) {
            std::cout << "start session on_write on " << std::this_thread::get_id() << std::endl;
            boost::ignore_unused(bytes_transferred);

            if(ec)
                return ott::util::fail(ec, "write");

            // Clear the buffer
            buffer_.consume(buffer_.size());

            // Do another read
            do_schedule();
            std::cout << "end session on_write on " << std::this_thread::get_id() << std::endl;
        }
    }
}