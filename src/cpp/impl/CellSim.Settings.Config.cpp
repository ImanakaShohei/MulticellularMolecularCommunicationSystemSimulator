#include "CellSim.Settings.Config.hpp"
#include "CellSim.Settings.Config.Cell.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.hpp"
#include "CellSim.Settings.Config.Optimization.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"
#include "CellSim.Settings.Config.SimulationModel.hpp"

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

    void Config::Load(::nlohmann::json const& config)
    {
        Cell::Load(config["cell"]);
        CellAlgorithm::Load(config["cell_algorithm"]);
        Optimization::Load(config["optimization"]);
        Simulation::Load(config["simulation"]);
        SimulationModel::Load(config["simulation_model"]);
    }
}