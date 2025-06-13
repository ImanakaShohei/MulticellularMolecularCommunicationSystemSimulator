#ifndef CELLSIM_CLI_CLIOPTIONACTIVATIONARGS_HPP
#define CELLSIM_CLI_CLIOPTIONACTIVATIONARGS_HPP

#include "base.hpp"

#include <map>

namespace CellSim::Cli
{
    struct CliOptionActivationArgs {
        const ::std::map<CliOptionType, CliOption*>* Options;

        constexpr CliOptionActivationArgs(const ::std::map<CliOptionType, CliOption*>* options) noexcept;
    };
}

namespace CellSim::Cli
{
    constexpr CliOptionActivationArgs::CliOptionActivationArgs(const ::std::map<CliOptionType, CliOption*>* options) noexcept
        : Options(options)
    {
    }
}

#endif //!CELLSIM_CLI_CLIOPTIONACTIVATIONARGS_HPP