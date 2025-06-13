#ifndef CELLSIM_CLI_IMAGEOPTION_HPP
#define CELLSIM_CLI_IMAGEOPTION_HPP

#include "base.hpp"
#include "CellSim.Cli.CliOption.hpp"

namespace CellSim::Cli
{
    class ImageOption final : public CliOption {
        public:

        ImageOption() = default;

        constexpr bool IsMatch(::std::string_view optionName) const noexcept override;
    };
}

namespace CellSim::Cli
{
    constexpr bool ImageOption::IsMatch(::std::string_view optionName) const noexcept
    {
        using namespace std;
        return optionName == "-h"sv || optionName == "--help"sv;
    }
}

#endif //!CELLSIM_CLI_IMAGEOPTION_HPP