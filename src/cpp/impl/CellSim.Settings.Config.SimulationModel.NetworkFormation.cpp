#include "CellSim.Settings.Config.SimulationModel.NetworkFormation.hpp"
#include "CellSim.Model.NetworkFormationModel.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.Text.CString.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    Model::CellSimulationModel::Params* Config::SimulationModel::NetworkFormation::Params::FromJson(
        ::nlohmann::json const& j
    )
    {
        if (j.is_null()) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Model.NetworkFormationModel.Params.FromJson.JsonError"
                )
            );
        }

        double adhesiveRepulsionFactor;
        double attractionFactor;
        double lambda;
        double maxRepulsionDistance;
        double minAttractionDistance;
        double remoteForceFactor;

        try {
            adhesiveRepulsionFactor = j.at("adhesiveRepulsionFactor").get<double>();
            attractionFactor = j.at("attractionFactor").get<double>();
            lambda = j.at("lambda").get<double>();
            maxRepulsionDistance = j.at("maxRepulsionDistance").get<double>();
            minAttractionDistance = j.at("minAttractionDistance").get<double>();
            remoteForceFactor = j.at("remoteForceFactor").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(
                Messages::Get(
                    "Model.NetworkFormationModel.Params.FromJson.JsonError"
                )
            );
        }

        if (adhesiveRepulsionFactor < 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.NetworkFormation.Load.Error.adhesiveRepulsionFactor"
                )
            );
        }
        if (attractionFactor < 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.NetworkFormation.Load.Error.attractionFactor"
                )
            );
        }
        if (lambda == 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.NetworkFormation.Load.Error.lambda"
                )
            );
        }
        if (maxRepulsionDistance <= 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.NetworkFormation.Load.Error.maxRepulsionDistance"
                )
            );
        }
        if (minAttractionDistance <= 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.NetworkFormation.Load.Error.minAttractionDistance"
                )
            );
        }
        if (remoteForceFactor < 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.NetworkFormation.Load.Error.remoteForceFactor"
                )
            );
        }
        
        if (maxRepulsionDistance >= minAttractionDistance) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.NetworkFormation.Load.Error.maxRepulsionDistance-minAttractionDistance"
                )
            );
        }

        return new Model::NetworkFormationModel::Params(
            adhesiveRepulsionFactor,
            attractionFactor,
            lambda,
            maxRepulsionDistance,
            minAttractionDistance,
            remoteForceFactor
        );
    }

    void Config::SimulationModel::NetworkFormation::Load(
        ::nlohmann::json const& config
    )
    {
        if (config.is_null()) return;
        
        try {
            s_maxAttractionDistance = config.at("maxAttractionDistance").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.NetworkFormation.Load.Error.JsonError"
                )
            );
        }

        
        if (s_maxAttractionDistance <= 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.NetworkFormation.Load.Error.maxAttractionDistance"
                )
            );
        }
        
    }
}