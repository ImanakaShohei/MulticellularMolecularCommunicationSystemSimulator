#ifndef CELLSIM_CLI_HELPOPTION_HPP
#define CELLSIM_CLI_HELPOPTION_HPP

#include "base.hpp"
#include "CellSim.Cli.FlagOption.hpp"

namespace CellSim::Cli
{
    class HelpOption final : public FlagOption {
        private:

        static constexpr ::std::string_view s_fullName = "--help";
        static constexpr ::std::string_view s_names = "-h, --help";

        public:

        HelpOption() = default;

        constexpr ::std::string_view FullName() const noexcept override;

        constexpr bool IsMatch(::std::string_view optionName) const noexcept override;

        constexpr ::std::string_view Names() const noexcept override;

        constexpr CliOptionType OptionType() const noexcept override;

        void Run(const CliOptions* sender, CliOptionArgs args) override;

        constexpr bool TakesControl() const noexcept override;
    };
}

namespace CellSim::Cli
{
    constexpr ::std::string_view HelpOption::FullName() const noexcept
    {
        return s_fullName;
    }

    constexpr bool HelpOption::IsMatch(::std::string_view optionName) const noexcept
    {
        using namespace std;
        return optionName == "-h"sv || optionName == "--help"sv;
    }

    constexpr ::std::string_view HelpOption::Names() const noexcept
    {
        return s_names;
    }

    constexpr CliOptionType HelpOption::OptionType() const noexcept
    {
        return CliOptionType::Help;
    }

    constexpr bool HelpOption::TakesControl() const noexcept
    {
        return true;
    }
}

#endif //!CELLSIM_CLI_HELPOPTION_HPP