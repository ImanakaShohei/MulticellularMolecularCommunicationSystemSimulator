#ifndef CELLSIM_CLI_PARAMETEROPTION_HPP
#define CELLSIM_CLI_PARAMETEROPTION_HPP

#include "base.hpp"
#include "CellSim.Cli.RepeatedValueOption.hpp"

#include <string>

namespace CellSim::Cli
{
    class ParamOption final : public RepeatedValueOption {
        private:

        static constexpr ::std::string_view s_fullName = "--param";
        static constexpr ::std::string_view s_names = "-p, --param";

        public:

        constexpr ::std::string_view FullName() const noexcept override;

        constexpr bool IsMatch(::std::string_view optionName) const noexcept override;

        constexpr ::std::string_view Names() const noexcept override;

        void OnActive(const CliOptions* sender, CliOptionActivationArgs args) override;

        constexpr CliOptionType OptionType() const noexcept override;

        constexpr bool TakesControl() const noexcept override;
    };
}

namespace CellSim::Cli
{
    constexpr ::std::string_view ParamOption::FullName() const noexcept
    {
        return s_fullName;
    }

    constexpr bool ParamOption::IsMatch(::std::string_view optionName) const noexcept
    {
        using namespace std;
        return optionName == "-p"sv || optionName == "--param"sv;
    }

    constexpr ::std::string_view ParamOption::Names() const noexcept
    {
        return s_names;
    }

    constexpr CliOptionType ParamOption::OptionType() const noexcept
    {
        return CliOptionType::Param;
    }

    constexpr bool ParamOption::TakesControl() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_CLI_PARAMETEROPTION_HPP