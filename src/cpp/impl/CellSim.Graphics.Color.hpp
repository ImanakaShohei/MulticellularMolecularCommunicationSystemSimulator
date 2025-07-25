#ifndef CELLSIM_GRAPHICS_COLOR_HPP
#define CELLSIM_GRAPHICS_COLOR_HPP

#include "base.hpp"
#include <string_view>

namespace CellSim::Graphics
{
    /// @brief ARGBカラー値
    struct Color {
        uint8_t A;
        uint8_t R;
        uint8_t G;
        uint8_t B;

        Color() = default;
        explicit Color(::std::string_view value);
        constexpr Color(uint8_t r, uint8_t g, uint8_t b) noexcept;
        constexpr Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b) noexcept;
    };
}

namespace CellSim::Graphics
{
    

    constexpr Color::Color(uint8_t r, uint8_t g, uint8_t b) noexcept
        : A(255)
        , R(r)
        , G(g)
        , B(b)
    {
    }

    constexpr Color::Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b) noexcept
        : A(a)
        , R(r)
        , G(g)
        , B(b)
    {
    }
}

#endif //!CELLSIM_GRAPHICS_COLOR_HPP