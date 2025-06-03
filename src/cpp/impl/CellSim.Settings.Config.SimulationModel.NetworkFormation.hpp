#ifndef CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_NETWORKFORMATION_HPP
#define CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_NETWORKFORMATION_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.SimulationModel.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::SimulationModel::NetworkFormation final {
        private:
        static inline double s_adhesiveRepulsionFactor;
        static inline double s_attractionFactor;
        static inline double s_lambda;
        static inline double s_maxAttractionDistance;
        static inline double s_maxRepulsionDistance;
        static inline double s_minAttractionDistance;
        static inline double s_remoteForceFactor;

        public:

        CELLSIM_STATIC_CLASS(NetworkFormation);
        
        /// @brief くっついた細胞同士に働く反発力の係数
        /// @return 
        [[nodiscard]] static double AdhesiveRepulsionFactor() noexcept;

        /// @brief 接着した細胞同士にかかる引力の係数
        [[nodiscard]] static double AttractionFactor() noexcept;

        [[nodiscard]] static double Lambda() noexcept;

        /// @brief 接着可能な最大距離
        [[nodiscard]] static double MaxAttractionDistance() noexcept;

        /// @brief 反発力が働く最大距離
        [[nodiscard]] static double MaxRepulsionDistance() noexcept;

        /// @brief 接着可能な最小距離
        [[nodiscard]] static double MinAttractionDistance() noexcept;

        /// @brief 遠隔力の係数
        [[nodiscard]] static double RemoteForceFactor() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline double Config::SimulationModel::NetworkFormation::AdhesiveRepulsionFactor() noexcept
    {
        return s_adhesiveRepulsionFactor;
    }

    inline double Config::SimulationModel::NetworkFormation::AttractionFactor() noexcept
    {
        return s_attractionFactor;
    }

    inline double Config::SimulationModel::NetworkFormation::Lambda() noexcept
    {
        return s_lambda;
    }

    inline double Config::SimulationModel::NetworkFormation::MaxAttractionDistance() noexcept
    {
        return s_maxAttractionDistance;
    }

    inline double Config::SimulationModel::NetworkFormation::MaxRepulsionDistance() noexcept
    {
        return s_maxRepulsionDistance;
    }

    inline double Config::SimulationModel::NetworkFormation::MinAttractionDistance() noexcept
    {
        return s_minAttractionDistance;
    }

    inline double Config::SimulationModel::NetworkFormation::RemoteForceFactor() noexcept
    {
        return s_remoteForceFactor;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_NETWORKFORMATION_HPP