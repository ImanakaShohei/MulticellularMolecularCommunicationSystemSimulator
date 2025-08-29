#ifndef CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERSPROUTING_HPP
#define CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERSPROUTING_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.SimulationModel.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    /// @brief クラスタスプラウトモデルの設定
    class Config::SimulationModel::ClusterSprouting final {
        private:

        static inline double s_contactDistance; //細胞同士がこの値より近づくと反発力が発生
        
        public:

        CELLSIM_STATIC_CLASS(ClusterSprouting);

        /// @brief 細胞同士がこの値より近づくと反発力が発生
        [[nodiscard]] static double ContactDistance() noexcept;
        

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline double Config::SimulationModel::ClusterSprouting::ContactDistance() noexcept
    {
        return s_contactDistance;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERSPROUTING_HPP