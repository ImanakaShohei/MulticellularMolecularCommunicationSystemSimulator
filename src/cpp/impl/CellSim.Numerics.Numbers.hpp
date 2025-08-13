#ifndef CELLSIM_NUMERICS_NUMBERS_HPP
#define CELLSIM_NUMERICS_NUMBERS_HPP

#include "base.hpp"

#include <string>
#include <string_view>

namespace CellSim::Numerics
{
    class Numbers final {
        public:

        template <NumberType TNum>
        static bool ToNumber(const char* str, TNum& result) noexcept;

        template <NumberType TNum>
        static bool ToNumber(::std::string str, TNum& result) noexcept;

        template <NumberType TNum>
        static bool ToNumber(::std::string_view str, TNum& result) noexcept;
    };
}

namespace CellSim::Numerics
{
    template <NumberType TNum>
    bool Numbers::ToNumber(const char* str, TNum& result) noexcept
    {
        if (str == nullptr) [[unlikely]] return false;

        return ToNumber<TNum>(::std::string(str), result);
    }

    template <NumberType TNum>
    bool Numbers::ToNumber(::std::string_view str, TNum& result) noexcept
    {
        return ToNumber<TNum>(::std::string(str.data(), str.size()), result);
    }
}

#endif //!CELLSIM_NUMERICS_NUMBERS_HPP