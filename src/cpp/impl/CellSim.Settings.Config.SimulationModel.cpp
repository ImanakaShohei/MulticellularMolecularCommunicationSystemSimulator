#include "CellSim.Settings.Config.SimulationModel.hpp"
#include "CellSim.Settings.Config.SimulationModel.CellGrowth.hpp"
#include "CellSim.Settings.Config.SimulationModel.ClusterFormation.hpp"
#include "CellSim.Settings.Config.SimulationModel.NetworkFormation.hpp"
#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::SimulationModel::Load(::nlohmann::json const& config)
    {
        ::std::string s;

        try {
            s = config.at("simulationType").get<::std::string>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.Load.Error.JsonError"));
        }

        if (s == "CellGrowth") s_simulationType = Model::CellSimulationType::CellGrowth;
        else if (s == "ClusterFormation") s_simulationType = Model::CellSimulationType::ClusterFormation;
        else if (s == "ClusterRotation") s_simulationType = Model::CellSimulationType::ClusterRotation;
        else if (s == "ClusterSprouting") s_simulationType = Model::CellSimulationType::ClusterSprouting;
        else if (s == "NetworkFormation") s_simulationType = Model::CellSimulationType::NetworkFormation;
        else if (s == "Null") s_simulationType = Model::CellSimulationType::Null;
        else if (s == "User") s_simulationType = Model::CellSimulationType::User;
        else [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.Load.Error.simulationType"));

        switch (s_simulationType) {
            case Model::CellSimulationType::CellGrowth: CellGrowth::Load(config["cellGrowthModel"]); break;
            case Model::CellSimulationType::ClusterFormation: ClusterFormation::Load(config["clusterFormation"]); break;
            case Model::CellSimulationType::ClusterRotation: break;
            case Model::CellSimulationType::ClusterSprouting: break;
            case Model::CellSimulationType::NetworkFormation: NetworkFormation::Load(config["networkFormation"]); break;
            case Model::CellSimulationType::Null: break;
            case Model::CellSimulationType::User: break;
        }

        
        
    }
}