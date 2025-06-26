#include "CellSim.Cli.RepeatedValueOption.hpp"

#include <stdexcept>

namespace CellSim::Cli
{
    ::std::string const& RepeatedValueOption::Value() const
    {
        throw ::std::runtime_error("::std::string const& RepeatedValueOption::Value() const");
    }
}