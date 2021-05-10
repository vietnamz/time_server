#pragma once

#include <cassert>
#include <iostream>
#include <fstream>

#include <boost/beast.hpp>

namespace ott
{

namespace util
{

    // report a failure
    void fail(boost::beast::error_code ec, char const* what);




} // util namespace
} // ott namespace


