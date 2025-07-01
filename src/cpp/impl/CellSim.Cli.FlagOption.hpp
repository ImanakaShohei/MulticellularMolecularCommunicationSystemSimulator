#ifndef CELLSIM_CLI_FLAGOPTION_HPP
#define CELLSIM_CLI_FLAGOPTION_HPP

#include "base.hpp"
#include "CellSim.Cli.CliOption.hpp"

namespace CellSim::Cli
{
    /// @brief 値を持たないオプション
    class FlagOption : public CliOption {
        public:

        [[noreturn]]
        void AddValue(::std::string_view value) override;
        
        constexpr bool HasValue() const noexcept override;
        constexpr bool IsRepeatable() const noexcept override;

        ::std::string const& Value() const override;

        ::std::vector<::std::string> const& Values() const override;
    };
}

namespace CellSim::Cli
{
    constexpr bool FlagOption::HasValue() const noexcept
    {
        return false;
    }

    constexpr bool FlagOption::IsRepeatable() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_CLI_FLAGOPTION_HPP