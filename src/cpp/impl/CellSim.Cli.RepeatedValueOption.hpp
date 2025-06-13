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

        [[nodiscard]] ::std::vector<::std::string> const& Values() const noexcept;
    };
}

namespace CellSim::Cli
{
    ::std::vector<::std::string> const& RepeatedValueOption::Values() const noexcept
    {
        return m_values;
    }
}

#endif //!CELLSIM_CLI_REPEATEDVALUEOPTION_HPP