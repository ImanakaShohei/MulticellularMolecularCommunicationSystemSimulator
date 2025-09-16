#include "CellSim.Settings.Config.SimulationModel.ClusterFormation.hpp"
#include "CellSim.Model.ClusterFormationModel.hpp"
#include "CellSim.Messages.hpp"

#include <stdexcept>
#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    Model::CellSimulationModel::Params* Config::SimulationModel::ClusterFormation::Params::FromJson(
        ::nlohmann::json const& j
    )
    {
        if (j.is_null()) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Model.ClusterFormationModel.Params.FromJson.JsonError"
                )
            );
        }

        double adhesiveRepulsionFactor;
        double lambda;
        double remoteForceFactor;   

        try {
            adhesiveRepulsionFactor = j.at("adhesiveRepulsionFactor").get<double>();
            lambda = j.at("lambda").get<double>();
            remoteForceFactor = j.at("remoteForceFactor").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(
                Messages::Get(
                    "Model.ClusterFormationModel.Params.FromJson.JsonError"
                )
            );
        }

        if (adhesiveRepulsionFactor < 0.0) {
            [[unlikely]] throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterFormation.Load.Error.adhesiveRepulsionFactor"
                )
            );
        }
        if (lambda == 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterFormation.Load.Error.lambda"
                )
            );
        }
        if (remoteForceFactor < 0.0) {
            [[unlikely]] throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterFormation.Load.Error.remoteForceFactor"
                )
            );
        }

        return new Model::ClusterFormationModel::Params(
            adhesiveRepulsionFactor,
            lambda,
            remoteForceFactor
        );
    }
}