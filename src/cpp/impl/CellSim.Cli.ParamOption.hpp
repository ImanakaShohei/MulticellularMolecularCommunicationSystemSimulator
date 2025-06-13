#ifndef CELLSIM_CLI_PARAMETEROPTION_HPP
#define CELLSIM_CLI_PARAMETEROPTION_HPP

#include "base.hpp"
#include "CellSim.Cli.CliOption.hpp"

#include <string>

namespace CellSim::Cli
{
    class ParamOption final : public CliOption {
        private:
        
        ::std::string m_param;

        public:
    };
}

#endif //!CELLSIM_CLI_PARAMETEROPTION_HPP