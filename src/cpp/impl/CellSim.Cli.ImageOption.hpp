#ifndef CELLSIM_CLI_IMAGEOPTION_HPP
#define CELLSIM_CLI_IMAGEOPTION_HPP

#include "base.hpp"
#include "CellSim.Cli.FlagOption.hpp"

namespace CellSim::Cli
{
    class ImageOption final : public FlagOption {
        private:

        static constexpr ::std::string_view s_fullName = "--image";
        static constexpr ::std::string_view s_names = "-i, --image";

        public:

        ImageOption() = default;

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
    constexpr ::std::string_view ImageOption::FullName() const noexcept
    {
        return s_fullName;
    }

    constexpr bool ImageOption::IsMatch(::std::string_view optionName) const noexcept
    {
        using namespace std;
        return optionName == "-h"sv || optionName == "--help"sv;
    }

    constexpr ::std::string_view ImageOption::Names() const noexcept
    {
        return s_names;
    }

    constexpr CliOptionType ImageOption::OptionType() const noexcept
    {
        return CliOptionType::Image;
    }

    constexpr bool ImageOption::TakesControl() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_CLI_IMAGEOPTION_HPP