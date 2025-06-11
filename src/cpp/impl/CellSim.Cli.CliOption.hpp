#ifndef CELLSIM_CLI_CLIOPTION_HPP
#define CELLSIM_CLI_CLIOPTION_HPP

#include "base.hpp"
#include <string_view>

namespace CellSim::Cli
{
    class CliOption {
        private:



        public:

        static CliOptionType Parse(::std::nullptr_t) = delete;
        [[nodiscard]] static CliOptionType Parse(::std::string_view view);
    };
}

#endif //!CELLSIM_CLI_CLIOPTION_HPP