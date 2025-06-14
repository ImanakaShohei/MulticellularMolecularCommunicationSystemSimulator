#ifndef CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_HPP
#define CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_HPP

#include "base.hpp"                   
#include "CellSim.Model.CellSimulationType.hpp"                                                                                                                              
#include "CellSim.Settings.Config.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::SimulationModel final {
        private:

        static inline Model::CellSimulationType s_simulationType;

        public:

        class CellGrowth;
        class ClusterFormation;
        class ClusterRotation;
        class ClusterSprouting;
        class NetworkFormation;

        CELLSIM_STATIC_CLASS(SimulationModel);

        /// @brief 
        [[nodiscard]] static Model::CellSimulationType SimulationType() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline Model::CellSimulationType Config::SimulationModel::SimulationType() noexcept
    {
        return s_simulationType;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_HPP