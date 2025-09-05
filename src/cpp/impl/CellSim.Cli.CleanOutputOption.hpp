#ifndef CELLSIM_CLI_CLEANOUTPUTOPTION_HPP
#define CELLSIM_CLI_CLEANOUTPUTOPTION_HPP

#include "base.hpp"
#include "CellSim.Cli.FlagOption.hpp"

namespace CellSim::Cli
{
    class CleanOutputOption final : public FlagOption {
        private:

        static constexpr ::std::string_view s_fullName = "--clean-output";

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
    constexpr ::std::string_view CleanOutputOption::FullName() const noexcept
    {
        return s_fullName;
    }

    constexpr bool CleanOutputOption::IsMatch(::std::string_view optionName) const noexcept
    {
        return optionName == s_fullName;
    }

    constexpr ::std::string_view CleanOutputOption::Names() const noexcept
    {
        return s_fullName;
    }

    constexpr CliOptionType CleanOutputOption::OptionType() const noexcept
    {
        return CliOptionType::CleanOutput;
    }

    constexpr bool CleanOutputOption::TakesControl() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_CLI_CLEANOUTPUTOPTION_HPP