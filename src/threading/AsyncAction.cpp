#include "AsyncAction.hpp"
#include <utility>
#include <exception>
#include <chrono>
#include <thread>

AsyncAction AsyncAction::promise_type::get_return_object()
{
    return AsyncAction(*this);
}

::std::suspend_never AsyncAction::promise_type::final_suspend() noexcept
{
    if (m__action != nullptr) {
        m__action->_isFinished = true;
        
        if (m__action->_hOther != nullptr) m__action->_hOther.resume();
    }

    return ::std::suspend_never{};
}

void AsyncAction::promise_type::unhandled_exception()
{
    if (m__action != nullptr) m__action->_isFinished = true;
    
    ::std::rethrow_exception(::std::current_exception());
}

AsyncAction::AsyncAction(AsyncAction&& right) noexcept
    : _handle(::std::move(right._handle))
    , _hOther(::std::move(right._hOther))
    , _isFinished(right._isFinished)
{
    right._handle = nullptr;

    if (_isFinished) return;

    _handle.promise().m__action = this;
}

AsyncAction::AsyncAction(promise_type& promise) : _handle(::std::coroutine_handle<promise_type>::from_promise(promise))
{
    promise.m__action = this;
}

AsyncAction::~AsyncAction()
{
    if (_handle == nullptr) return;
    if (_isFinished) return;

    _handle.promise().m__action = nullptr;
}

void AsyncAction::await_suspend(::std::coroutine_handle<> h)
{
    if (_isFinished) h.resume();
    else _hOther = h;
}

void AsyncAction::getResult() const noexcept
{
    using namespace ::std::chrono;

    while (!_isFinished) {
        ::std::this_thread::sleep_for(1ms);
    }
}