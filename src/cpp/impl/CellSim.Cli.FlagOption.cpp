#include "CellSim.Cli.FlagOption.hpp"
#include "CellSim.Messages.hpp"
#include <stdexcept>

namespace CellSim::Cli
{
    void FlagOption::AddValue(::std::string_view value)
    {
        throw ::std::runtime_error(Messages::Get("Cli.FlagOption.AddValue.Error"));
    }

    ::std::string const& FlagOption::Value() const
    {
        throw ::std::runtime_error("::std::string const& FlagOption::Value() const");
    }

    ::std::vector<::std::string> const& FlagOption::Values() const
    {
        throw ::std::runtime_error("::std::vector<::std::string> const& FlagOption::Values() const");
    }
}