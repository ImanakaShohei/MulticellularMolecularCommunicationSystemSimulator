#ifndef CELLSIM_CLI_CLIOPTION_HPP
#define CELLSIM_CLI_CLIOPTION_HPP

#include "base.hpp"
#include <string_view>

namespace CellSim::Cli
{
    /// @brief コマンドラインオプション
    class CliOption {
        protected:

        bool m_isEnabled;

        constexpr CliOption() noexcept;
        constexpr CliOption(bool isEnabled) noexcept;

        public:

        /// @brief このオプションが有効かどうか
        [[nodiscard]] constexpr bool IsEnabled() const noexcept;

        /// @brief 
        /// @param optionName 
        /// @return 
        virtual bool IsMatch(::std::string_view optionName) const noexcept = 0;

        static CliOptionType Parse(::std::nullptr_t) = delete;
        [[nodiscard]] static CliOptionType Parse(::std::string_view view);
        
    };
}

namespace CellSim::Cli
{
    constexpr CliOption::CliOption() noexcept
        : m_isEnabled(false)
    {
    }

    constexpr CliOption::CliOption(bool isEnabled) noexcept
        : m_isEnabled(isEnabled)
    {
    }
}

#endif //!CELLSIM_CLI_CLIOPTION_HPP