#ifndef CELLSIM_CLI_VALUEOPTION_HPP
#define CELLSIM_CLI_VALUEOPTION_HPP

#include "base.hpp"
#include "CellSim.Cli.CliOption.hpp"

#include <string>

namespace CellSim::Cli
{
    /// @brief 値を持つオプション
    class ValueOption : public CliOption {
        private:

        ::std::string m_value;

        ValueOption() = default;

        public:

        /// @brief 値
        [[nodiscard]] constexpr ::std::string const& Value() const noexcept;
    };
}

namespace CellSim::Cli
{
    constexpr ::std::string const& ValueOption::Value() const noexcept
    {
        return m_value;
    }
}

#endif //!CELLSIM_CLI_VALUEOPTION_HPP