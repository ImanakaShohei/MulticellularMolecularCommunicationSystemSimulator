#include "CellSim.Settings.Config.SimulationModel.NetworkFormation.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.Text.CString.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::SimulationModel::NetworkFormation::Load(::nlohmann::json const& config)
    {
        throw ::std::runtime_error(
            Text::CString::Format(
                Messages::Get("NotImplemented"),
                "void Config::SimulationModel::NetworkFormation::Load(::nlohmann::json const&)"
            )
        );
    }
}