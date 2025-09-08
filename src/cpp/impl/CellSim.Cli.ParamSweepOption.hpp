#ifndef CELLSIM_CLI_PARAMSWEEPOPTION_HPP
#define CELLSIM_CLI_PARAMSWEEPOPTION_HPP

#include "base.hpp"
#include "CellSim.Cli.RepeatedValueOption.hpp"

#include <string_view>
#include <nlohmann/json_fwd.hpp>

namespace CellSim::Cli
{
    class ParamSweepOption final : public RepeatedValueOption {
        private:

        static constexpr ::std::string_view s_fullName = "--param-sweep";

        template <Numerics::NumberType TNum>
        static void s_sweep(
            ::std::string_view first,
            ::std::string_view second,
            ::std::string_view third,
            ::std::string const& paramName,
            ::std::vector<::std::string>::const_iterator current,
            ::std::vector<::std::string>::const_iterator end,
            nlohmann::json& config,
            ::std::string const& path,
            CliOptionArgs args
        );

        static void s_run(
            ::std::vector<::std::string>::const_iterator current,
            ::std::vector<::std::string>::const_iterator end,
            ::std::string const& path,
            CliOptionArgs args
        );

        public:

        constexpr ::std::string_view FullName() const noexcept override;

        constexpr bool IsMatch(::std::string_view optionName) const noexcept override;

        constexpr ::std::string_view Names() const noexcept override;

        void Run(const CliOptions* sender, CliOptionArgs args) override;

        constexpr CliOptionType OptionType() const noexcept override;

        constexpr bool TakesControl() const noexcept override;
    };
}

namespace CellSim::Cli
{
    constexpr ::std::string_view ParamSweepOption::FullName() const noexcept
    {
        return s_fullName;
    }

    constexpr bool ParamSweepOption::IsMatch(::std::string_view optionName) const noexcept
    {
        return optionName == s_fullName;
    }

    constexpr ::std::string_view ParamSweepOption::Names() const noexcept
    {
        return s_fullName;
    }

    constexpr CliOptionType ParamSweepOption::OptionType() const noexcept
    {
        return CliOptionType::ParamSweep;
    }

    constexpr bool ParamSweepOption::TakesControl() const noexcept
    {
        return true;
    }
}

#endif //!CELLSIM_CLI_PARAMSWEEPOPTION_HPP