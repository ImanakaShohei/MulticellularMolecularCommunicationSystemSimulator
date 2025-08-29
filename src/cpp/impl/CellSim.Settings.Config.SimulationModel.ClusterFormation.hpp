#ifndef CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERFORMATION_HPP
#define CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERFORMATION_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.SimulationModel.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::SimulationModel::ClusterFormation final {
        private:
        public:

        CELLSIM_STATIC_CLASS(ClusterFormation);

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERFORMATION_HPP