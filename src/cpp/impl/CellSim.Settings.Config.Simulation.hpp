#ifndef CELLSIM_SETTINGS_CONFIG_SIMULATION_HPP
#define CELLSIM_SETTINGS_CONFIG_SIMULATION_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    /// @brief シミュレーション共通設定
    class Config::Simulation final {
        private:

        static inline double s_deltaTime;
        static inline double s_fieldRadiusX;
        static inline double s_fieldRadiusY;
        static inline double s_fieldRadiusZ;

        public:

        /// @brief 1ステップあたりのシミュレーション内時間
        [[nodiscard]] static double DeltaTime() noexcept;

        /// @brief フィールドのX方向の半径
        [[nodiscard]] static double FieldRadiusX() noexcept;

        /// @brief フィールドのY方向の半径
        [[nodiscard]] static double FieldRadiusY() noexcept;

        /// @brief フィールドのZ方向の半径
        [[nodiscard]] static double FieldRadiusZ() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline double Config::Simulation::DeltaTime() noexcept
    {
        return s_deltaTime;
    }

    inline double Config::Simulation::FieldRadiusX() noexcept
    {
        return s_fieldRadiusX;
    }

    inline double Config::Simulation::FieldRadiusY() noexcept
    {
        return s_fieldRadiusY;
    }

    inline double Config::Simulation::FieldRadiusZ() noexcept
    {
        return s_fieldRadiusZ;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATION_HPP