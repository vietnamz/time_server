#pragma once


//! stl
#include <algorithm>
#include <string>
#include <thread>
#include <iostream>
#include <functional>
#include <cstdlib>
#include <memory>
#include <vector>

//! boost
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/strand.hpp>
#include <boost/make_unique.hpp>
#include <boost/optional.hpp>


namespace ott
{
    namespace http
    {

        class HttpSession : public std::enable_shared_from_this<HttpSession>
        {
            class queue
            {
                enum { limit = 1024 };
                struct work
                {
                    virtual ~work() = default;
                    virtual void operator()() = 0;
                };
                HttpSession& self_;
                std::vector<std::unique_ptr<work>> items_;
                public:
                explicit queue(HttpSession& self) : self_(self)
                {
                    static_assert(limit > 0, "queue limit must be positive");
                    items_.reserve(limit);
                }
                bool isFull() const;
                bool onWrite();
                template<bool isRequest, class Body, class Fields>
                void operator()(boost::beast::http::message<isRequest, Body, Fields>&& msg);
            };
            boost::beast::tcp_stream stream_;
            boost::beast::flat_buffer buffer_;
            queue queue_;

            boost::optional<boost::beast::http::request_parser<boost::beast::http::string_body>> parser_;
        public:
            HttpSession(
                    boost::asio::ip::tcp::socket socker
                    ) : stream_(std::move(socker)), queue_(*this) {}
            void run();
        private:
            void doRead();
            void onRead(boost::beast::error_code ec, std::size_t bytes_transferred);
            void onWrite(bool close, boost::beast::error_code ec, std::size_t bytes_transferred);
            void doClose();
        };

    } // http namespace
} // ott namespace
