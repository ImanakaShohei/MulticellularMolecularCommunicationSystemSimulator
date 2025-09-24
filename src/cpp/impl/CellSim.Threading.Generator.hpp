#ifndef CELLSIM_THREADING_GENERATOR_HPP
#define CELLSIM_THREADING_GENERATOR_HPP

#include "base.hpp"
#include <coroutine>

// https://github.com/KongkongNT15/KongkongLibrary/blob/main/src/include/klib/Definitions/Kongkong.Threading.Generator.h

namespace CellSim::Threading
{
    template <class T>
    class Generator final {
        public:

        struct Iterator;
        struct promise_type final {
            private:
            T _value;

            Generator* _pGenerator;
            Iterator* _pIterator;

            friend Generator;
            friend Iterator;

            public:

            constexpr promise_type() noexcept
                : _value()
                , _pIterator(nullptr)
                , _pGenerator(nullptr)
            {
            }

            Generator get_return_object() noexcept { return *this; }

            static constexpr ::std::suspend_always initial_suspend() noexcept { return {}; }
            static constexpr ::std::suspend_always final_suspend() noexcept { return {}; }

            static constexpr void return_void() noexcept {}

            [[noreturn]]
            void unhandled_exception();

            ::std::suspend_always yield_value(
                T const& value
            ) noexcept(::std::is_nothrow_constructible_v<T>)
            {
                _value = value;
                return {};
            }

            ::std::suspend_always yield_value(
                T&& value
            ) noexcept
            {
                _value = ::std::move(value);
                return {};
            }

            T __getValue()
            {
                return _value;
            }
            constexpr bool __hasRefenrece() const noexcept { return _pGenerator != nullptr && _pIterator != nullptr; }
            constexpr bool __noReference() const noexcept { return _pGenerator == nullptr || _pIterator == nullptr; }

            
        };

        using handleType = ::std::coroutine_handle<promise_type>;

        class Iterator final {
            private:
            handleType _h_coro;
            bool _done;

            Iterator(handleType h) noexcept
                : _h_coro(h)
                , _done(h.done())
            {
                h.promise()._pIterator = this;
            }

            friend Generator;
            friend promise_type;

            public:

            constexpr Iterator() noexcept
                : _h_coro(nullptr)
                , _done(true)
            {
            }

            Iterator(Iterator const&) = delete;
            constexpr Iterator(Iterator&& right) noexcept
                : _h_coro(right._h_coro)
                , _done(right._done)
            {
                right._h_coro = nullptr;
            }

            ~Iterator()
            {
                if (!_h_coro) return;
                
                auto& promise = _h_coro.promise();

                promise._pIterator = nullptr;

                if (promise._pGenerator == nullptr) _h_coro.destroy();
            }

            Iterator& operator=(Iterator const&) = delete;

            Iterator& operator++()
            {
                //if (!_h_coro) [[unlikely]] throw InvalidOperationException(u"破棄されたオブジェクトにアクセスしようとしました");
                _h_coro.resume();

                _done = _h_coro.done();

                return *this;
            }

            friend constexpr bool operator!=(Iterator const& left, Iterator const& right) noexcept { return left._done != right._done; }

            T operator*() const
            {
                //if (!_h_coro) [[unlikely]] throw InvalidOperationException(u"破棄されたオブジェクトにアクセスしようとしました");
                return _h_coro.promise().__getValue();
            }

            
        };

        Generator(Generator const&) = delete;
        constexpr Generator(Generator&& right) noexcept
            : _h(right._h)
        {
            right._h = nullptr;
        }

        ~Generator()
        {
            if (!_h) return;
            
            auto& promise = _h.promise();

            promise._pGenerator = nullptr;

            if (promise._pIterator == nullptr) _h.destroy();
        }

        Generator& operator=(Generator const&) = delete;

        [[nodiscard]]
        Iterator begin()
        {
            _h.resume();
            return Iterator(_h);
        }

        [[nodiscard]] static constexpr Iterator end() noexcept { return Iterator(); }

        [[nodiscard]]
        bool IsFinished() const noexcept { return _h.done(); }

        [[nodiscard]]
        bool IsRunning() const noexcept { return !_h.done(); }

        private:

        handleType _h;
        bool _begun;

        Generator(promise_type& promise) noexcept
            : _h(handleType::from_promise(promise))
        {
            promise._pGenerator = this;
        }
    };
}

namespace CellSim::Threading
{
    template <class T>
    void Generator<T>::promise_type::unhandled_exception()
    {
        auto h = _pGenerator->_h;
        _pGenerator->_h = nullptr;

        if (_pIterator != nullptr) _pIterator->_h_coro = nullptr;

        h.destroy();
        
        ::std::rethrow_exception(::std::current_exception());
    }
}






#endif //!CELLSIM_THREADING_GENERATOR_HPP