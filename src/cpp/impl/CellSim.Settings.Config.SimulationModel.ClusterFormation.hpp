#ifndef CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERFORMATION_HPP
#define CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERFORMATION_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.SimulationModel.hpp"

namespace CellSim::Settings
{
    class Config::SimulationModel::ClusterFormation final {
        private:

        static inline double s_adhesiveRepulsionFactor;
        static inline double s_lambda;
        static inline double s_remoteForceFactor;

        public:

        CELLSIM_STATIC_CLASS(ClusterFormation);

        /// @brief くっついた細胞同士に働く反発力の係数
        /// @return 
        [[nodiscard]] static double AdhesiveRepulsionFactor() noexcept;

        [[nodiscard]] static double Lambda() noexcept;

        /// @brief 遠隔力の係数
        [[nodiscard]] static double RemoteForceFactor() noexcept;
    };
}

namespace CellSim::Settings
{
    inline double Config::SimulationModel::ClusterFormation::AdhesiveRepulsionFactor() noexcept
    {
        return s_adhesiveRepulsionFactor;
    }

    inline double Config::SimulationModel::ClusterFormation::Lambda() noexcept
    {
        return s_lambda;
    }

    inline double Config::SimulationModel::ClusterFormation::RemoteForceFactor() noexcept
    {
        return s_remoteForceFactor;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERFORMATION_HPP