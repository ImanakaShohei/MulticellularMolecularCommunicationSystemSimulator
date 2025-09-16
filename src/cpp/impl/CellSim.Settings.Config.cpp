#include "CellSim.Settings.Config.hpp"
#include "CellSim.Settings.Config.Cell.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.hpp"
#include "CellSim.Settings.Config.CellBehavior.hpp"
#include "CellSim.Settings.Config.Molecular.hpp"
#include "CellSim.Settings.Config.Optimization.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"
#include "CellSim.Settings.Config.SimulationModel.hpp"
#include "../CellSim.Settings.Config.UserSettings.hpp"

#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    void Config::s_loadUnsafe(const char* filePath)
    {
        ::nlohmann::json config;
        ::std::ifstream ifs(filePath);
        
        if (!ifs) [[unlikely]] throw ::std::invalid_argument("Failed to open the specified file.");

        ifs >> config;

        return Load(config);
    }

    void Config::Load()
    {
        s_loadUnsafe("config.json");
    }

    void Config::Load(const char* filePath)
    {
        if (filePath == nullptr) [[unlikely]] throw ::std::runtime_error("The parameter filePath is nullptr.");
        s_loadUnsafe(filePath);
    }

    void Config::Load(::std::string const& filePath)
    {
        s_loadUnsafe(filePath.c_str());
    }

    void Config::Load(::nlohmann::json& config)
    {
        Simulation::Load(config["simulation"]);
        SimulationModel::Load(config["simulationModel"]);

        Cell::Load(config["cell"]);
        CellAlgorithm::Load(config["cellAlgorithm"]);
        Molecular::Load(config["molecular"]);
        Optimization::Load(config["optimization"]);
        UserSettings::Load(config["userSettings"]);
    }

    ::nlohmann::json Config::OpenJsonFile(::std::string const& filePath)
    {
        ::nlohmann::json config;
        ::std::ifstream ifs(filePath);
        
        if (!ifs) [[unlikely]] throw ::std::invalid_argument("Failed to open the specified file.");

        ifs >> config;

        return config;
    }
}