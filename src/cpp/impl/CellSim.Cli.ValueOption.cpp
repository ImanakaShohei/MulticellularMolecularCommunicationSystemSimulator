#include "CellSim.Cli.ValueOption.hpp"

#include <stdexcept>

namespace CellSim::Cli
{
    ::std::vector<::std::string> const& ValueOption::Values() const
    {
        throw ::std::runtime_error(
            "::std::vector<::std::string> const& ValueOption::Values() const"
        );
    }
}