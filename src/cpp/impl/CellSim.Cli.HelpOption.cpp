#include "CellSim.Cli.HelpOption.hpp"
#include "CellSim.Cli.CliOptionArgs.hpp"
#include "CellSim.Text.CString.hpp"
#include "CellSim.Messages.hpp"

#include <stdexcept>

namespace CellSim::Cli
{
    void HelpOption::Run(const CliOptions*, CliOptionArgs args)
    {
        for (auto& pair : *args.Options) {
            if (pair.first != CliOptionType::Help && pair.second->IsEnabled()) [[unlikely]] {
                throw ::std::runtime_error(
                    Text::CString::Format(
                        Messages::Get("Cli.CliOptions.m_enableOption.Error.TakesControlError").c_str(),
                        this->Names().data(),
                        pair.second->Names().data()
                    )
                );
            }
        }
        
        ::puts(Messages::Get("Cli.HelpOption.Message").c_str());
    }
}