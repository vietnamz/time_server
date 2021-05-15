#pragma once

#include <algorithm>
#include <exception>
#include <variant>
#include <coroutine>

namespace ott
{
    namespace util
    {
        template<typename T>
        struct task
        {
            template<typename V>
            struct promise
            {
                task<T> get_return_object() noexcept { return {this};}
                std::suspend_never initial_suspend() noexcept { return {};}
                auto final_suspend() noexcept {
                    struct final_awaitable
                    {
                        bool await_ready() const noexcept 
                        {
                            return false;
                        }
                        void await_suspend(std::coroutine_handle<promise<T>> coro) noexcept
                        {
                            auto& promise = coro.promise();
                            if(promise.continuation_)
                                promise.continuation_();
                        }
                        void await_resume() const noexcept {}
                    };
                    return final_awaitable{};
                }
                template<typename U>
                void return_value(U&& value) noexcept(std::is_nothrow_constructible_v<T, decltype(std::forward<U>(value))>)
                {
                    result_.template emplace<1>(std::forward<U>(value));
                }
                void unhandled_exception() noexcept(std::is_nothrow_constructible_v<std::exception_ptr,std::exception_ptr>){
                    result_.template emplace<2>(std::current_exception());
                }
                bool is_ready() const noexcept { return result_.index() != 0; }
                T &&get_result(){
                   if(result_.index() == 2)
                   {
                       std::rethrow_exception(std::get<2>(result_));
                   }
                   return std::move(std::get<1>(result_));
                }
                std::variant<std::monostate, V, std::exception_ptr> result_;
                std::coroutine_handle<> continuation_;
            };
            
            /* data */
            using promise_type = promise<T>;
            task() = default;
            auto operator co_await() const noexcept {
                struct awaitable {

                    bool await_ready() const noexcept {
                        return promise_.get_result();
                    }
                    std::coroutine_handle<> await_suspend(std::coroutine_handle<> continuation) const noexcept {
                        promise_.continuation_ = continuation;
                        return std::coroutine_handle<promise<T>>::from_promise(promise_);
                    }

                    T&& await_resume() const {
                        return promise_.get_result();
                    }
                    promise<T> &promise_;
                };
                return awaitable{*promise_};
            }
            private:
            task(promise<T> * promise) : promise_{promise} {}
            promise<T>* promise_ = nullptr;
            template<typename V> friend struct promise;   
        };
    }  // namespace util
} // namespace ott

