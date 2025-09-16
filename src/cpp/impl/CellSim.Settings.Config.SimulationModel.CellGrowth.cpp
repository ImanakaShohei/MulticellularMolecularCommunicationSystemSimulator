#include "CellSim.Settings.Config.SimulationModel.CellGrowth.hpp"
#include "CellSim.Model.CellGrowthModel.hpp"
#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    Model::CellSimulationModel::Params* Config::SimulationModel::CellGrowth::Params::FromJson(
        ::nlohmann::json const& j
    )
    {
        if (j.is_null()) [[unlikely]] {
             throw ::std::runtime_error(
                Messages::Get(
                    "Model.CellGrowthModel.Params.FromJson.JsonError"
                )
            );
        }

        double adhesiveRepulsionFactor;

        try {
            adhesiveRepulsionFactor = j.at("adhesiveRepulsionFactor").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(
                Messages::Get(
                    "Model.CellGrowthModel.Params.FromJson.JsonError"
                )
            );
        }

        if (adhesiveRepulsionFactor < 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.CellGrowth.Load.Error.adhesiveRepulsionFactor"
                )
            );
        }

        return new Model::CellGrowthModel::Params(
            adhesiveRepulsionFactor
        );
    }
}