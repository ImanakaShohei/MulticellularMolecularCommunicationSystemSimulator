#include "CellSim.Settings.Config.SimulationModel.NetworkFormation.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.Text.CString.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::SimulationModel::NetworkFormation::Load(::nlohmann::json const& config)
    {
        try {
            s_adhesiveRepulsionFactor = config.at("adhesiveRepulsionFactor").get<double>();
            s_attractionFactor = config.at("attractionFactor").get<double>();
            s_lambda = config.at("lambda").get<double>();
            s_maxAttractionDistance = config.at("maxAttractionDistance").get<double>();
            s_maxRepulsionDistance = config.at("maxRepulsionDistance").get<double>();
            s_minAttractionDistance = config.at("minAttractionDistance").get<double>();
            s_remoteForceFactor = config.at("remoteForceFactor").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.JsonError"));
        }

        if (s_adhesiveRepulsionFactor < 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.adhesiveRepulsionFactor"));
        if (s_attractionFactor < 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.attractionFactor"));
        if (s_lambda == 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.lambda"));
        if (s_maxAttractionDistance <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.maxAttractionDistance"));
        if (s_maxRepulsionDistance <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.maxRepulsionDistance"));
        if (s_minAttractionDistance <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.minAttractionDistance"));
        if (s_remoteForceFactor < 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.remoteForceFactor"));
        
        if (s_minAttractionDistance >= s_maxAttractionDistance) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.minAttractionDistance-maxAttractionDistance"));
        if (s_maxRepulsionDistance >= s_minAttractionDistance) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.maxRepulsionDistance-minAttractionDistance"));
    }
}