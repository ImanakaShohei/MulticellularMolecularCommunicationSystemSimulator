#include "CellSim.Settings.Config.SimulationModel.ClusterSprouting.hpp"
#include "CellSim.Model.ClusterSproutingModel.hpp"
#include "CellSim.Messages.hpp"

#include <stdexcept>
#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    Model::CellSimulationModel::Params* Config::SimulationModel::ClusterSprouting::Params::FromJson(
        ::nlohmann::json const& j
    )
    {
        if (j.is_null()) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Model.ClusterSproutingModel.Params.FromJson.JsonError"
                )
            );
        }

        size_t adhesionThreshold;
        double coefficientCd;
        double followerAttractionFactor;
        double globalAttractionFactor;
        double lambda;
        double leaderRepulsionFactor;
        double leaderRepulsionMaxDistance;
        double leaderRepulsionMinDistance;

        try {
            adhesionThreshold = j.at("adhesionThreshold").get<size_t>();
            coefficientCd = j.at("coefficientCd").get<double>();
            followerAttractionFactor = j.at("followerAttractionFactor").get<double>();
            globalAttractionFactor = j.at("globalAttractionFactor").get<double>();
            lambda = j.at("lambda").get<double>();
            leaderRepulsionFactor = j.at("leaderRepulsionFactor").get<double>();
            leaderRepulsionMaxDistance = j.at("leaderRepulsionMaxDistance").get<double>();
            leaderRepulsionMinDistance = j.at("leaderRepulsionMinDistance").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterSprouting.Load.Error.JsonError"
                )
            );
        }

        if (coefficientCd < 0.0) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterSprouting.Load.Error.coefficientCd"
                )
            );
        }
        if (followerAttractionFactor < 0.0) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterSprouting.Load.Error.followerAttractionFactor"
                )
            );
        }
        if (globalAttractionFactor < 0.0) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterSprouting.Load.Error.globalAttractionFactor"
                )
            );
        }
        if (lambda == 0.0) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterSprouting.Load.Error.lambda"
                )
            );
        }
        if (leaderRepulsionFactor < 0.0) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterSprouting.Load.Error.leaderRepulsionFactor"
                )
            );
        }
        if (leaderRepulsionMaxDistance < 0.0) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterSprouting.Load.Error.leaderRepulsionMaxDistance"
                )
            );
        }
        if (leaderRepulsionMinDistance < 0.0) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterSprouting.Load.Error.leaderRepulsionMinDistance"
                )
            );
        }
        
        return new Model::ClusterSproutingModel::Params(
            adhesionThreshold,
            coefficientCd,
            followerAttractionFactor,
            globalAttractionFactor,
            lambda,
            leaderRepulsionFactor,
            leaderRepulsionMaxDistance,
            leaderRepulsionMinDistance
        );
    }

    void Config::SimulationModel::ClusterSprouting::Load(
        ::nlohmann::json const& config
    )
    {
        if (config.is_null()) return;
        
        try {
            s_contactDistance = config.at("contactDistance").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterSprouting.Load.Error.JsonError"
                )
            );
        }

        if (s_contactDistance < 0.0) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterSprouting.Load.Error.contactDistance"
                )
            );
        }
    }
}