#include "CellSim.Settings.Config.SimulationModel.ClusterSprouting.hpp"
#include "CellSim.Messages.hpp"

#include <stdexcept>
#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    void Config::SimulationModel::ClusterSprouting::Load(::nlohmann::json const& config)
    {
        if (config.is_null()) return;
        
        try {
            s_adhesionThreshold = config.at("adhesionThreshold").get<size_t>();
            s_coefficientCd = config.at("coefficientCd").get<double>();
            s_contactDistance = config.at("contactDistance").get<double>();
            s_followerAttractionFactor = config.at("followerAttractionFactor").get<double>();
            s_globalAttractionFactor = config.at("globalAttractionFactor").get<double>();
            s_lambda = config.at("lambda").get<double>();
            s_leaderRepulsionFactor = config.at("leaderRepulsionFactor").get<double>();
            s_leaderRepulsionMaxDistance = config.at("leaderRepulsionMaxDistance").get<double>();
            s_leaderRepulsionMinDistance = config.at("leaderRepulsionMinDistance").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.JsonError"));
        }

        if (s_coefficientCd < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.coefficientCd"));
        if (s_contactDistance < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.contactDistance"));
        if (s_followerAttractionFactor < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.followerAttractionFactor"));
        if (s_globalAttractionFactor < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.globalAttractionFactor"));
        if (s_lambda == 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.lambda"));
        if (s_leaderRepulsionFactor < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.leaderRepulsionFactor"));
        if (s_leaderRepulsionMaxDistance < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.leaderRepulsionMaxDistance"));
        if (s_leaderRepulsionMinDistance < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.leaderRepulsionMinDistance"));
        
        if (s_contactDistance >= s_leaderRepulsionMinDistance) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.contactDistance-leaderRepulsionMinDistance"));
    }
}