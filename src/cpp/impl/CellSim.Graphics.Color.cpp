#include "CellSim.Graphics.Color.hpp"

#include <stdexcept>

namespace CellSim::Graphics
{
    Color::Color(
        ::std::string_view value
    )
        : A(255)
    {
        if (value.size() != 7) [[unlikely]] {
            throw ::std::invalid_argument(
                "Color::Color(::std::string_view): value.size() != 7"
            );
        }
        if (value[0] != '#') [[unlikely]] {
            throw ::std::invalid_argument(
                "Color::Color(::std::string_view): value[0] != '#'"
            );
        }

        auto f = [] (const char* p) {
            uint8_t values[2];

            for (size_t i = 0; i < 2; i++) {
                char c = p[i];

                if ('0' <= c && c <= '9') {
                    values[i] = c - '0';
                    continue;
                }
                if ('A' <= c &&  c <= 'F') {
                    values[i] = static_cast<uint8_t>(c - 'A' + 10);
                    continue;
                }
                if ('a' <= c &&  c <= 'f') {
                    values[i] = static_cast<uint8_t>(c - 'a' + 10);
                    continue;
                }

                throw ::std::invalid_argument(
                    "Color::Color(::std::string_view): invalid color value."
                );
            }

            return static_cast<uint8_t>(values[0] * 16 + values[1]);
        };

        R = f(&value[1]);
        G = f(&value[3]);
        B = f(&value[5]);
    }
}