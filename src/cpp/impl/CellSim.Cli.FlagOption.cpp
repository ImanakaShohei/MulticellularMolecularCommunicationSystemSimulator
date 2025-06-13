#include "CellSim.Cli.FlagOption.hpp"
#include "CellSim.Messages.hpp"
#include <stdexcept>

namespace CellSim::Cli
{
    void FlagOption::AddValue(::std::string_view value)
    {
        throw ::std::runtime_error(Messages::Get("Cli.FlagOption.AddValue.Error"));
    }
}