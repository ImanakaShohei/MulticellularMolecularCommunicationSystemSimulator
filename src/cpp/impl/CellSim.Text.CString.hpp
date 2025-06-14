#ifndef CELLSIM_TEXT_CSTRING_HPP
#define CELLSIM_TEXT_CSTRING_HPP

#include "base.hpp"

#include <string>

namespace CellSim::Text
{
    class CString final {
        public:

        template <class... Args>
        [[nodiscard]] static ::std::string Format(const char* format, Args&&... args)
        {
            int result = ::snprintf(nullptr, 0, format, ::std::forward<Args>(args)...);

            ::std::string s(result, '\0');

            ::snprintf(s.data(), result + 1, format, ::std::forward<Args>(args)...);

            return s;
        }

        template <class... Args>
        [[nodiscard]] static ::std::string Format(::std::string const& format, Args&&... args)
        {
            return Format(format.c_str(), ::std::forward<Args>(args)...);
        }
    };
}

#endif //!CELLSIM_TEXT_CSTRING_HPP