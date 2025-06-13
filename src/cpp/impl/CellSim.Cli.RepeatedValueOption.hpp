#ifndef CELLSIM_CLI_REPEATEDVALUEOPTION_HPP
#define CELLSIM_CLI_REPEATEDVALUEOPTION_HPP

#include "base.hpp"
#include "CellSim.Cli.CliOption.hpp"

#include <vector>
#include <string>

namespace CellSim::Cli
{
    /// @brief 複数回指定できるオプション
    class RepeatedValueOption : public CliOption {
        private:

        ::std::vector<::std::string> m_values;

        public:

        constexpr bool HasValue() const noexcept override;
        constexpr bool IsRepeatable() const noexcept override;

        [[nodiscard]] ::std::vector<::std::string> const& Values() const noexcept;
    };
}

namespace CellSim::Cli
{
    constexpr bool RepeatedValueOption::HasValue() const noexcept
    {
        return true;
    }

    constexpr bool RepeatedValueOption::IsRepeatable() const noexcept
    {
        return true;
    }

    ::std::vector<::std::string> const& RepeatedValueOption::Values() const noexcept
    {
        return m_values;
    }
}

#endif //!CELLSIM_CLI_REPEATEDVALUEOPTION_HPP