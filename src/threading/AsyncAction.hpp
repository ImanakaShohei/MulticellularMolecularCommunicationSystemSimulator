#pragma once

#include <coroutine>
#include <mutex>

class AsyncAction final {
    public:

    constexpr void await_resume() const noexcept {}

        struct promise_type final {
            AsyncAction get_return_object();
            constexpr void return_void() noexcept {}

            constexpr promise_type() noexcept : m__action(nullptr) {}

            static constexpr auto initial_suspend() noexcept { return ::std::suspend_never{}; }
            ::std::suspend_never final_suspend() noexcept;

            [[noreturn]]
            void unhandled_exception();

            AsyncAction* m__action;
        };

        constexpr bool await_ready() const noexcept { return false; }
        void await_suspend(std::coroutine_handle<> h);

        constexpr AsyncAction() : _handle(nullptr) {}
        AsyncAction(AsyncAction const&) = delete;

        AsyncAction(AsyncAction&& right) noexcept;

        ~AsyncAction();

        AsyncAction& operator=(AsyncAction const&) = delete;

        void getResult() const noexcept;

        private:

        using _handleType = ::std::coroutine_handle<promise_type>;

        _handleType _handle;
        ::std::coroutine_handle<> _hOther;
        bool _isFinished;

        explicit AsyncAction(promise_type& promise);
};