#ifndef CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_NETWORKFORMATION_HPP
#define CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_NETWORKFORMATION_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.SimulationModel.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::SimulationModel::NetworkFormation final {
        private:
        static inline double s_maxAttractionDistance;

        public:

        CELLSIM_STATIC_CLASS(NetworkFormation);

        /// @brief 接着可能な最大距離
        [[nodiscard]] static double MaxAttractionDistance() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline double Config::SimulationModel::NetworkFormation::MaxAttractionDistance() noexcept
    {
        return s_maxAttractionDistance;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_NETWORKFORMATION_HPP