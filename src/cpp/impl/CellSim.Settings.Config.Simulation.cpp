#include "CellSim.Settings.Config.Simulation.hpp"
#include "CellSim.Messages.hpp"
#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::Simulation::Load(::nlohmann::json& config)
    {
        if (config.is_null()) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Simulation.Load.Error.JsonError"));

        try {
            s_deltaTime = config.at("deltaTime").get<double>();
            s_enable2DMode = config.at("enable2DMode").get<bool>();
            s_fieldRadius = config.at("fieldRadius").get<double>();
            s_imageSize = config.at("imageSize").get<int32_t>();
            s_outputInterval = config.at("outputInterval").get<int32_t>();
            s_totalSteps = config.at("totalSteps").get<uint64_t>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.Simulation.Load.Error.JsonError"));
        }
        

        if (s_deltaTime <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Simulation.Load.Error.deltaTime"));
        if (s_fieldRadius < 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Simulation.Load.Error.fieldRadius"));
        if (s_imageSize <= 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Simulation.Load.Error.imageSize"));
        if (s_outputInterval <= 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Simulation.Load.Error.outputInterval"));
        if (s_totalSteps == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Simulation.Load.Error.totalSteps"));
    }
}