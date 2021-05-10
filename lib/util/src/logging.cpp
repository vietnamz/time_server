#include "logging.hpp"

#include <boost/beast.hpp>
#include <boost/log/trivial.hpp>

namespace ott
{

    namespace util
    {
        void fail(boost::beast::error_code ec, char const* what)
        {
            std::cerr << what << ": " << ec.message() << "\n";
        }
    } // util namespace
} // ott namespace


