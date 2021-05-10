//
// Created by john on 09/05/2021.
//

#pragma once

#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>         // std::chrono::seconds

//! boost
#include "boost/date_time/posix_time/posix_time.hpp"

namespace pt = boost::posix_time;


namespace ott
{

    namespace websocket
    {


        struct timer {
            struct promise_type
            {
                std::string current_time;
                timer get_return_object()
                {
                    return timer(std::coroutine_handle<promise_type>::from_promise(*this));
                }
                auto initial_suspend() { return std::suspend_never{};}
                auto final_suspend() noexcept { return std::suspend_never{}; }
                //void return_void() {}
                void unhandled_exception() {}
                void return_value(std::string value){
                    std::cout << "timer::promise_type - return_value - input : value = " << value << "\n";
                    current_time = std::move(value);
                }
            };
            std::coroutine_handle<promise_type> _coroutine = nullptr;
            explicit timer(std::coroutine_handle<promise_type> coroutine): _coroutine(coroutine){
                std::cout << "call timer constructor\n";
            }
            ~timer()
            {
                if(_coroutine) {
                    std::cout << "call timer destructor \n";
                    _coroutine.destroy();
                    _coroutine = nullptr;
                }
            }
            timer() {
                std::cout << "call timer default constructor\n";
            }
            timer(timer const&) = delete;
            timer* operator=(timer const&) = delete;

            timer(timer&& other) : _coroutine(other._coroutine)
            {
                std::cout << "call timer move constructor\n";
                other._coroutine = nullptr;
            }

            timer& operator=(timer&& other)
            {
                if(&other != this )
                {
                    _coroutine = other._coroutine;
                    other._coroutine = nullptr;
                }
                return *this;
            }
            void resume(){
                _coroutine.resume();
            }

            std::string get() {
                pt::ptime current_date_microseconds = pt::microsec_clock::local_time();
                long milliseconds = current_date_microseconds.time_of_day().total_milliseconds();
                pt::time_duration current_time_milliseconds = pt::milliseconds(milliseconds);
                pt::ptime current_date_milliseconds(current_date_microseconds.date(),
                                                    current_time_milliseconds);
                std::stringstream ss;
                ss << current_date_microseconds;
                std::cout << "call get() ss.str() " << ss.str() << "\n" ;
                //std::cout << "call get() " << _coroutine.promise().current_time << "\n";
                return ss.str();

                /*
                 *  FIXME: this below statement did not work as expected. not so sure why.
                 */
                //return _coroutine.promise().current_time;
            }
        };

        struct wail_every_5_secs
        {
            bool await_ready()
            {
                return false;
            }
            void await_suspend(std::coroutine_handle<> ch)
            {
                std::cout << "start wail_every_5_secs await_suspend \n";
                std::this_thread::sleep_for(std::chrono::seconds(5));
                ch.resume();
                std::cout << "end wail_every_5_secs await_suspend \n";
            }
            auto await_resume() {
                std::cout << "start wail_every_5_secs await_resume \n";
                pt::ptime current_date_microseconds = pt::microsec_clock::local_time();
                long milliseconds = current_date_microseconds.time_of_day().total_milliseconds();
                pt::time_duration current_time_milliseconds = pt::milliseconds(milliseconds);
                pt::ptime current_date_milliseconds(current_date_microseconds.date(),
                                                    current_time_milliseconds);
                std::stringstream ss;
                ss << current_date_microseconds;
                std::cout << "current_date_microseconds " << ss.str() << "\n" ;
                return ss.str();
            }
        };


        timer make_timer();

    }
}