#ifndef CELLSIM_SETTINGS_CONFIG_HPP
#define CELLSIM_SETTINGS_CONFIG_HPP

#include "base.hpp"

#include <string>
#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config final {
        private:

        static void s_loadUnsafe(const char* filePath);

        public:

        class Cell;
        class CellAlgorithm;
        class Optimization;
        class Simulation;
        class SimulationModel;
        class UserSettings;

        CELLSIM_STATIC_CLASS(Config);

        static void Load();
        static void Load(const char* filePath);
        static void Load(::std::string const& filePath);
        static void Load(::nlohmann::json const& config);
    };
}

#endif //!CELLSIM_SETTINGS_CONFIG_HPP