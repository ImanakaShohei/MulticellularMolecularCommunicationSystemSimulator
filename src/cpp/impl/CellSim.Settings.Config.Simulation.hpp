#ifndef CELLSIM_SETTINGS_CONFIG_SIMULATION_HPP
#define CELLSIM_SETTINGS_CONFIG_SIMULATION_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::Simulation final {
        private:

        static inline double s_deltaTime;

        public:

        /// @brief 1ステップあたりのシミュレーション内時間
        [[nodiscard]] static double DeltaTime() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline double Config::Simulation::DeltaTime() noexcept
    {
        return s_deltaTime;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATION_HPP