#ifndef CELLSIM_CLI_OUTPUTOPTION_HPP
#define CELLSIM_CLI_OUTPUTOPTION_HPP

#include "base.hpp"
#include "CellSim.Cli.ValueOption.hpp"

namespace CellSim::Cli
{
    class OutputOption final : public ValueOption {
        private:

        ::std::string_view s_fullName = "--output";
        ::std::string_view s_names = "-o, --output";

        public:

        OutputOption();

        void AddValue(::std::string_view value) override;

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
    constexpr ::std::string_view OutputOption::FullName() const noexcept
    {
        return s_fullName;
    }

    constexpr bool OutputOption::IsMatch(::std::string_view optionName) const noexcept
    {
        using namespace std;
        return optionName == "-o"sv || optionName == "--output"sv;
    }

    constexpr ::std::string_view OutputOption::Names() const noexcept
    {
        return s_names;
    }

    constexpr CliOptionType OutputOption::OptionType() const noexcept
    {
        return CliOptionType::Output;
    }

    constexpr bool OutputOption::TakesControl() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_CLI_OUTPUTOPTION_HPP