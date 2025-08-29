#ifndef CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERROTATION_HPP
#define CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERROTATION_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.SimulationModel.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    /// @brief クラスタ回転モデルの設定
    class Config::SimulationModel::ClusterRotation final {
        private:
        public:

        CELLSIM_STATIC_CLASS(ClusterRotation);

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERROTATION_HPP