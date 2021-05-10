//
// Created by john on 09/05/2021.
//
//! boost
#include "boost/date_time/posix_time/posix_time.hpp"
#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <future>
#include <chrono>         // std::chrono::seconds
#include <chrono>         // std::chrono::seconds

namespace pt = boost::posix_time;
struct task{
    struct promise_type {
        task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

auto switch_to_new_thread(std::jthread& out) {
    struct awaitable {
        std::jthread* p_out;
        bool await_ready() {

            return true;
        }
        void await_suspend(std::coroutine_handle<> h) {
            std::jthread& out = *p_out;
            if (out.joinable())
                throw std::runtime_error("Output jthread parameter not empty");
            out = std::jthread([h] { h.resume(); });
            // Potential undefined behavior: accessing potentially destroyed *this
            // std::cout << "New thread ID: " << p_out->get_id() << '\n';
            std::cout << "New thread ID: " << out.get_id() << '\n'; // this is OK
        }
        void await_resume() {
            std::cout << "await resume" << std::endl;
        }
    };
    return awaitable{&out};
}


task resuming_on_new_thread(std::jthread& out) {
    std::cout << "Coroutine started on thread: " << std::this_thread::get_id() << '\n';
    while(true) {
        co_await switch_to_new_thread(out);
        // awaiter destroyed here
        std::cout << "Coroutine resumed on thread: " << std::this_thread::get_id() << '\n';
        co_await switch_to_new_thread(out);
        std::cout << "Coroutine resumed on thread: " << std::this_thread::get_id() << '\n';
    }
}
struct resumable_thing {
    struct promise_type
    {
        int _value;
        resumable_thing get_return_object()
        {
            return resumable_thing(std::coroutine_handle<promise_type>::from_promise(*this));
        }
        auto initial_suspend() { return std::suspend_never{};}
        auto final_suspend() noexcept { return std::suspend_always{}; }
        //void return_void() {}
        void return_value(int value) {
            _value = value;
        }
        void unhandled_exception() {}
    };
    std::coroutine_handle<promise_type> _coroutine = nullptr;
    explicit resumable_thing(std::coroutine_handle<promise_type> coroutine): _coroutine(coroutine){
        std::cout << "call resumable_thing constructor\n";
        //init();
    }
    int get() {
        return _coroutine.promise()._value;
    }
    ~resumable_thing()
    {
        std::cout << "call resumable_thing destructor\n";
        stop = true;
        if(_coroutine) {_coroutine.destroy();}
    }
    resumable_thing() {
        std::cout << "call resumable_thing default constructor\n";
        //init();
    }
    resumable_thing(resumable_thing const&) = delete;
    resumable_thing* operator=(resumable_thing const&) = delete;

    resumable_thing(resumable_thing&& other) : _coroutine(other._coroutine)
    {
        std::cout << "call resumable_thing move constructor\n";
        other.stop = true;
        other._coroutine = nullptr;
    }

    resumable_thing& operator=(resumable_thing&& other)
    {
        if(&other != this )
        {
            _coroutine = other._coroutine;
            other._coroutine = nullptr;
        }
    }
    volatile bool  stop = false;
    void resume(){
        _coroutine.resume();
    }

    void init() {
        while(!stop) {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            _coroutine.resume();
        }
    }

};
resumable_thing counter()
{
    std::cout << "counter: called\n";
    while(true) {
        co_await std::suspend_always{};
        std::cout << "counter : resumed (#" << "continue" << ")\n";
    }

}

/*
template <typename T, typename... Arguments>
struct std::coroutine_traits<std::future<T>, Arguments...>
{
    struct promise_type
    {
        std::promise<T> _promise;
        std::future<T> get_return_object() { return _promise.get_future();}
        auto initial_suspend() {return std::suspend_never();}
        auto final_suspend() noexcept {return std::suspend_never();}

        template<typename U>
        void return_value(U&& value) { _promise.set_value(std::forward<U>(value));}
        void set_exception(std::exception_ptr ex ) { _promise.set_exception(std::move(ex));}
        void unhandled_exception() {}

    };
};
template<typename T>
struct future_awaiter
{
    std::future<T>& _f;
    bool await_ready()
    {
        true;
    }
    void await_suspend(std::coroutine_handle<> ch)
    {
        _f.wait_for(std::chrono::seconds(5));
        ch.resume();
    }
    auto await_resume() {
        return _f.get();
    }
};
template <typename T>
future_awaiter<T> operator co_await (std::future<T>& value)
{
    return future_awaiter<T>{value};
}

std::future<int> get_value()
{
    std::cout << "get_value: called \n";
    int result = co_await std::async([]
                        {
                            return 30;
                        });
    std::cout << "get_value : resumed (#" << "continue" << ")\n";
    co_return result;
}
*/

struct wail_every_5_secs
{
    bool await_ready()
    {
       return true;
    }
    void await_suspend(std::coroutine_handle<> ch)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        ch.resume()
        ;std::cout <<"await_suspend\n";

    }
    auto await_resume() {
        // handle something

        return 40;
    }
};


resumable_thing get_value()
{
    std::cout << "get_value: called \n";
    co_await wail_every_5_secs{};
    std::cout << "get_value : resumed (#" << "continue" << ")\n";
    pt::ptime current_date_microseconds = pt::microsec_clock::local_time();
    long milliseconds = current_date_microseconds.time_of_day().total_milliseconds();
    pt::time_duration current_time_milliseconds = pt::milliseconds(milliseconds);

    pt::ptime current_date_milliseconds(current_date_microseconds.date(),
                                        current_time_milliseconds);
    std::stringstream ss;
    ss << current_date_microseconds;
    std::cout <<"await resume\n";
    co_return 29;
}



int main() {
    //std::jthread out;
    //auto t = resuming_on_new_thread(out);
    std::cout << "main: calling counter\n";
    auto the_counter = get_value();
    std::cout << "main: resuming counter\n";
    //the_counter.resume();
    std::cout << "main :value is " << the_counter.get() << "\n";
    std::cout << "main: done\n";

}
