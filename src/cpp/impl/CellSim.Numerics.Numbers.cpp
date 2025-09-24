#include "CellSim.Numerics.Numbers.hpp"
#include <sstream>

namespace CellSim::Numerics
{
    template <NumberType TNum>
    bool Numbers::ToNumber(
        ::std::string str,
        TNum& result
    ) noexcept
    {
        try {
            size_t size = str.size();
            str.push_back(' ');

            ::std::istringstream sin(::std::move(str));

            sin >> result;

            return static_cast<bool>(sin) && sin.tellg() == size;
        }
        catch (...) {
            return false;
        }
    }

    template bool Numbers::ToNumber(::std::string, char&);
    template bool Numbers::ToNumber(::std::string, short&);
    template bool Numbers::ToNumber(::std::string, int&);
    template bool Numbers::ToNumber(::std::string, long&);
    template bool Numbers::ToNumber(::std::string, long long&);
    template bool Numbers::ToNumber(::std::string, unsigned char&);
    template bool Numbers::ToNumber(::std::string, unsigned short&);
    template bool Numbers::ToNumber(::std::string, unsigned int&);
    template bool Numbers::ToNumber(::std::string, unsigned long&);
    template bool Numbers::ToNumber(::std::string, unsigned long long&);
    template bool Numbers::ToNumber(::std::string, signed char&);
    template bool Numbers::ToNumber(::std::string, float&);
    template bool Numbers::ToNumber(::std::string, double&);
    template bool Numbers::ToNumber(::std::string, long double&);
}