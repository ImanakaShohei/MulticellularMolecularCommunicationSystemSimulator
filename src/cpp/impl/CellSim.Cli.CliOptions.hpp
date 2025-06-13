#ifndef CELLSIM_CLI_CLIOPTIONS_HPP
#define CELLSIM_CLI_CLIOPTIONS_HPP

#include "base.hpp"

#include <vector>

namespace CellSim::Cli
{
    struct CliOptions {
        private:

        ::std::vector<CliOption*> m_options;

        public:

        CliOptions();
        CliOptions(CliOptions const&) = delete;
        ~CliOptions();

        CliOptions& operator=(CliOptions const&) = delete;
    };
}

#endif //!CELLSIM_CLI_CLIOPTIONS_HPP