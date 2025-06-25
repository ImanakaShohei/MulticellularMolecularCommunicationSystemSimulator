#ifndef CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CELLGROWTHMODEL_HPP
#define CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CELLGROWTHMODEL_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.SimulationModel.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::SimulationModel::CellGrowth final {
        private:

        static inline double s_adhesiveRepulsionFactor;

        public:

        CELLSIM_STATIC_CLASS(CellGrowth);

        /// @brief くっついた細胞同士に働く反発力の係数
        [[nodiscard]] static double AdhesiveRepulsionFactor() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline double Config::SimulationModel::CellGrowth::AdhesiveRepulsionFactor() noexcept
    {
        return s_adhesiveRepulsionFactor;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CELLGROWTHMODEL_HPP