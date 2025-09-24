#include "CellSim.Cli.OutputOption.hpp"
#include "CellSim.Cli.CliOptionActivationArgs.hpp"

#include <filesystem>

namespace CellSim::Cli
{
    OutputOption::OutputOption()
        : ValueOption("./result/")
    {
    }

    void OutputOption::AddValue(
        ::std::string_view value
    )
    {
        m_value = value;

        switch (value.back()) {
            case '\\':
            case '/':
                break;

            default:
            {
                m_value.push_back(
                    static_cast<char>(::std::filesystem::path::preferred_separator)
                );
                break;
            }
        }
    }

    void OutputOption::OnActive(
        const CliOptions*,
        CliOptionActivationArgs
    )
    {
    }
}