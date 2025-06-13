#ifndef CELLSIM_CLI_CLIOPTIONS_HPP
#define CELLSIM_CLI_CLIOPTIONS_HPP

#include "base.hpp"
#include "CellSim.Cli.CliOptionType.hpp"

#include <map>

namespace CellSim::Cli
{
    struct CliOptions {
        private:

        ::std::map<CliOptionType, CliOption*> m_options;

        public:

        CliOptions();
        CliOptions(CliOptions const&) = delete;
        ~CliOptions();

        CliOptions& operator=(CliOptions const&) = delete;
    };
}

#endif //!CELLSIM_CLI_CLIOPTIONS_HPP