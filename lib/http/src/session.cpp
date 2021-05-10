#include "session.hpp"

//! stl
#include <thread>
#include <iostream>
#include <cstdlib>
#include <vector>

//! boost
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/make_unique.hpp>
#include <boost/optional.hpp>


//! local
#include "request.hpp"

namespace ott
{
namespace http
{

bool HttpSession::queue::isFull() const
{
    return items_.size() >= limit;
}
bool HttpSession::queue::onWrite()
{
    BOOST_ASSERT(!items_.empty());
    auto const wasFull = isFull();
    items_.erase(items_.begin());
    if ( !items_.empty()) (*items_.front())();
    return wasFull;
}
template<bool isRequest, class Body, class Fields>
void HttpSession::queue::operator()(boost::beast::http::message<isRequest, Body, Fields>&& msg)
{
    struct workImpl : work
    {
        HttpSession& self_;
        boost::beast::http::message<isRequest, Body, Fields> msg_;
        workImpl(
                HttpSession& self,
                boost::beast::http::message<isRequest, Body, Fields>&& msg)
                : self_(self)
                  , msg_(std::move(msg)) {}
        void operator()()
        {
             boost::beast::http::async_write(
                self_.stream_,
                msg_,
                boost::beast::bind_front_handler(
                        &HttpSession::onWrite,
                        self_.shared_from_this(),
                        msg_.need_eof()
                        )
                    );
        }
    };
    items_.push_back(boost::make_unique<workImpl>(self_, std::move(msg)));
    if ( items_.size() == 1) (*items_.front())();
}
void HttpSession::run()
{
    std::cout << "start New session" << std::endl ;
    boost::beast::net::dispatch(
                stream_.get_executor(),
                boost::beast::bind_front_handler(&HttpSession::doRead, this->shared_from_this()));
    std::cout << "end New session" << std::endl ;
}
void HttpSession::doRead()
{
    std::cout << "start doRead" << std::endl;
    parser_.emplace();
    parser_->body_limit(10000);
    stream_.expires_after(std::chrono::seconds(30));
        
    boost::beast::http::async_read(
                stream_,
                buffer_,
                *parser_,
                boost::beast::bind_front_handler(
                    &HttpSession::onRead,
                    shared_from_this()
                    )
                );
    std::cout << "end doRead" << std::endl;

}
void HttpSession::onRead(boost::beast::error_code ec, std::size_t bytes_transferred)
{
    std::cout << "start onRead" << std::endl;
    boost::ignore_unused(bytes_transferred);
    if ( ec == boost::beast::http::error::end_of_stream) return doClose();
    if (ec) return fail(ec, "read");
    handleRequest(parser_->release(), queue_);
    if ( !queue_.isFull()) doRead();
    std::cout << "end onRead" << std::endl;
}
void HttpSession::onWrite(bool close, boost::beast::error_code ec, std::size_t bytes_transferred)
{
    std::cout << "start onWrite with " << bytes_transferred << std::endl;
    boost::ignore_unused(bytes_transferred);
    if(ec) return fail(ec, "write");
    if ( close ) return doClose();
    if ( queue_.onWrite()) doRead();
    std::cout << "end onWrite" << std::endl;
}

void HttpSession::doClose() 
{
    std::cout << "start doClose" << std::endl;
    boost::beast::error_code ec;
    stream_.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
    std::cout << "end doClose" << std::endl;
}


} // http namespace
} // ott namespace
