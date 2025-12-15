#include "CellSim.Settings.Config.SimulationModel.hpp"
#include "CellSim.Settings.Config.SimulationModel.CellGrowth.hpp"
#include "CellSim.Settings.Config.SimulationModel.ClusterFormation.hpp"
#include "CellSim.Settings.Config.SimulationModel.ClusterRotation.hpp"
#include "CellSim.Settings.Config.SimulationModel.ClusterSprouting.hpp"
#include "CellSim.Settings.Config.SimulationModel.NetworkFormation.hpp"
#include "CellSim.Messages.hpp"

#include "../CellSim.Settings.Config.SimulationModel.User.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    Model::CellSimulationModel::Params* Config::SimulationModel::Params::FromJson(
        ::nlohmann::json& j,
        Model::CellSimulationType type
    )
    {
        if (j.is_null()) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Model.CellSimulationModel.Params.FromJson.JsonError"
                )
            );
        }

        switch (type) {
            case Model::CellSimulationType::CellGrowth:       return CellGrowth::Params::FromJson(j["cellGrowth"]);
            case Model::CellSimulationType::ClusterFormation: return ClusterFormation::Params::FromJson(j["clusterFormation"]);
            case Model::CellSimulationType::ClusterRotation:  return ClusterRotation::Params::FromJson(j["clusterRotation"]);
            case Model::CellSimulationType::ClusterSprouting: return ClusterSprouting::Params::FromJson(j["clusterSprouting"]);
            case Model::CellSimulationType::NetworkFormation: return NetworkFormation::Params::FromJson(j["networkFormation"]);
            case Model::CellSimulationType::Null:             return nullptr;
            case Model::CellSimulationType::User:             return User::Params::FromJson(j["user"]);
            default: [[unlikely]]
            {
                throw ::std::invalid_argument(
                    Messages::Get(
                        "Model.CellSimulationModel.Params.FromJson.TypeError"
                    )
                );
            }
        }
    }

    void Config::SimulationModel::Load(
        ::nlohmann::json& config
    )
    {
        if (config.is_null()) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.Load.Error.JsonError"
                )
            );
        }

        ::std::string s;

        try {
            s = config.at("simulationType").get<::std::string>();
        }
        catch (...) {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.Load.Error.JsonError"
                )
            );
        }

        if (s == "CellGrowth") {
            s_simulationType = Model::CellSimulationType::CellGrowth;
        }
        else if (s == "ClusterFormation") {
            s_simulationType = Model::CellSimulationType::ClusterFormation;
        }
        else if (s == "ClusterRotation") {
            s_simulationType = Model::CellSimulationType::ClusterRotation;
        }
        else if (s == "ClusterSprouting") {
            s_simulationType = Model::CellSimulationType::ClusterSprouting;
            ClusterSprouting::Load(config["clusterSprouting"]);
        }
        else if (s == "NetworkFormation") {
            s_simulationType = Model::CellSimulationType::NetworkFormation;
            NetworkFormation::Load(config["networkFormation"]);
        }
        else if (s == "Null") {
            s_simulationType = Model::CellSimulationType::Null;
        }
        else if (s == "User") {
            s_simulationType = Model::CellSimulationType::User;
            User::Load(config["user"]);
        }
        else [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.Load.Error.simulationType"
                )
            );
        }
        
    }
}