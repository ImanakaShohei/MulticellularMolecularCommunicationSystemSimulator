#include "CellSim.Cli.CliOptions.hpp"
#include "CellSim.Cli.ImageOption.hpp"

namespace CellSim::Cli
{
    CliOptions::CliOptions()
        : m_options()
    {
        // ここで、オプションを処理する順番を決めます

        auto addOption = [this] (CliOption* option) {
            m_options.emplace(option->OptionType(), option);
        };
    }

    CliOptions::~CliOptions()
    {
        for (auto pair : m_options) {
            delete pair.second;
        }
    }
}