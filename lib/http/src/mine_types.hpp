#pragma once

#include <string>
#include <boost/beast/core.hpp>


namespace ott
{

    namespace http
    {

        boost::beast::string_view
        mime_type(boost::beast::string_view path);

    } // http namespace

} // ott namespace
