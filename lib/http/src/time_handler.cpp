//
// Created by john on 08/05/2021.
//

#include "time_handler.hpp"

//! stl
#include <iostream>

//! boost
#include "boost/date_time/posix_time/posix_time.hpp"


namespace pt = boost::posix_time;

namespace ott
{
    namespace http
    {
        bool time_handler::operator()(const std::string_view context) {
            if(!is_valid(context))
            {
                if ( next_.get() == nullptr ) return false;
                return next()(context);
            }
            // handle something
            pt::ptime current_date_microseconds = pt::microsec_clock::local_time();
            long milliseconds = current_date_microseconds.time_of_day().total_milliseconds();
            pt::time_duration current_time_milliseconds = pt::milliseconds(milliseconds);

            pt::ptime current_date_milliseconds(current_date_microseconds.date(),
                                                current_time_milliseconds);
            std::stringstream ss;
            ss << current_date_microseconds;
            result_ = ss.str();
            return true;
        }
    }
}