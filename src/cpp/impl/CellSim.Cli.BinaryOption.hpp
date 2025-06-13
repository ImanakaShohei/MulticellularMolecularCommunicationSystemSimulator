#ifndef CELLSIM_CLI_BINARYOPTION_HPP
#define CELLSIM_CLI_BINARYOPTION_HPP

#include "base.hpp"
#include "CellSim.Cli.FlagOption.hpp"

namespace CellSim::Cli
{
    class BinaryOption final : public FlagOption {
        private:

        static constexpr ::std::string_view s_fullName = "--binary";
        static constexpr ::std::string_view s_names = "-b, --binary";

        public:

        BinaryOption() = default;

        constexpr ::std::string_view FullName() const noexcept override;

        bool IsMatch(::std::string_view optionName) const noexcept override;

        constexpr ::std::string_view Names() const noexcept override;

        void OnActive(const CliOptions* sender, CliOptionActivationArgs args) override;

        constexpr CliOptionType OptionType() const noexcept override;

        constexpr bool TakesControl() const noexcept override;
    };
}

namespace CellSim::Cli
{
    constexpr ::std::string_view BinaryOption::FullName() const noexcept
    {
        return s_fullName;
    }

    bool BinaryOption::IsMatch(::std::string_view optionName) const noexcept
    {
        using namespace std;
        return optionName == "-b"sv || optionName == "--binary"sv;
    }

    constexpr ::std::string_view BinaryOption::Names() const noexcept
    {
        return s_names;
    }

    constexpr CliOptionType BinaryOption::OptionType() const noexcept
    {
        return CliOptionType::Binary;
    }

    constexpr bool BinaryOption::TakesControl() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_CLI_BINARYOPTION_HPP