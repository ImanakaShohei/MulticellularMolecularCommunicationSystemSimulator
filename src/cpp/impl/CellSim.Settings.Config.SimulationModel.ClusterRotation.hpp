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

        static inline double s_adhesionDistanceThreshold;
        static inline double s_adhesionForceFactor;
        static inline double s_centralForceFactor;
        static inline double s_repulsionFactor;
        static inline double s_repulsionMaxDistance;

        public:

        CELLSIM_STATIC_CLASS(ClusterRotation);

        /// @brief 細胞同士がこの値より近いと接着力が働く
        [[nodiscard]] static double AdhesionDistanceThreshold() noexcept;

        /// @brief 接着力にかける係数
        [[nodiscard]] static double AdhesionForceFactor() noexcept;

        /// @brief 中心力にかける係数
        [[nodiscard]] static double CentralForceFactor() noexcept;

        /// @brief 反発力の係数
        [[nodiscard]] static double RepulsionFactor() noexcept;

        /// @brief 細胞同士がこの値より近いと反発する
        [[nodiscard]] static double RepulsionMaxDistance() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline double Config::SimulationModel::ClusterRotation::AdhesionDistanceThreshold() noexcept
    {
        return s_adhesionDistanceThreshold;
    }

    inline double Config::SimulationModel::ClusterRotation::AdhesionForceFactor() noexcept
    {
        return s_adhesionForceFactor;
    }

    inline double Config::SimulationModel::ClusterRotation::CentralForceFactor() noexcept
    {
        return s_centralForceFactor;
    }

    inline double Config::SimulationModel::ClusterRotation::RepulsionFactor() noexcept
    {
        return s_repulsionFactor;
    }

    inline double Config::SimulationModel::ClusterRotation::RepulsionMaxDistance() noexcept
    {
        return s_repulsionMaxDistance;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERROTATION_HPP