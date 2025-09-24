#ifndef CELLSIM_CLI_CLIOPTIONARGS_HPP
#define CELLSIM_CLI_CLIOPTIONARGS_HPP

#include "base.hpp"

#include <map>

namespace CellSim::Cli
{
    struct CliOptionArgs {
        const ::std::map<CliOptionType, CliOption*>* Options;

        constexpr CliOptionArgs(
            const ::std::map<CliOptionType, CliOption*>* options
        ) noexcept;
    };
}

namespace CellSim::Cli
{
    constexpr CliOptionArgs::CliOptionArgs(
        const ::std::map<CliOptionType, CliOption*>* options
    ) noexcept
        : Options(options)
    {
    }
}

#endif //!CELLSIM_CLI_CLIOPTIONARGS_HPP