#ifndef CELLSIM_CLI_CLIOPTIONTYPE_HPP
#define CELLSIM_CLI_CLIOPTIONTYPE_HPP

#include "base.hpp"

namespace CellSim::Cli
{
    enum class CliOptionType {
        Binary,
        Csv,
        Help,
        Image,
        NoCleanOutput,
        Output,
        Param,
        ParamSweep,
        Setting,
        Video,
    };
}

#endif //!CELLSIM_CLI_CLIOPTIONTYPE_HPP