#ifndef CELLSIM_CLI_CLEANOUTPUTOPTION_HPP
#define CELLSIM_CLI_CLEANOUTPUTOPTION_HPP

#include "base.hpp"
#include "CellSim.Cli.FlagOption.hpp"

namespace CellSim::Cli
{
    class NoCleanOutputOption final : public FlagOption {
        private:

        static constexpr ::std::string_view s_fullName = "--no-clean-output";

        public:

        constexpr ::std::string_view FullName() const noexcept override;

        constexpr bool IsMatch(::std::string_view optionName) const noexcept override;

        constexpr ::std::string_view Names() const noexcept override;

        constexpr CliOptionType OptionType() const noexcept override;

        constexpr bool TakesControl() const noexcept override;
    };
}

namespace CellSim::Cli
{
    constexpr ::std::string_view NoCleanOutputOption::FullName() const noexcept
    {
        return s_fullName;
    }

    constexpr bool NoCleanOutputOption::IsMatch(::std::string_view optionName) const noexcept
    {
        return optionName == s_fullName;
    }

    constexpr ::std::string_view NoCleanOutputOption::Names() const noexcept
    {
        return s_fullName;
    }

    constexpr CliOptionType NoCleanOutputOption::OptionType() const noexcept
    {
        return CliOptionType::NoCleanOutput;
    }

    constexpr bool NoCleanOutputOption::TakesControl() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_CLI_CLEANOUTPUTOPTION_HPP