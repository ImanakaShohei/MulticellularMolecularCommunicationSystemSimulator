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
        static inline bool s_enable2DMode;
        static inline double s_fieldRadiusX;
        static inline double s_fieldRadiusY;
        static inline double s_fieldRadiusZ;
        static inline uint64_t s_totalSteps;

        public:

        /// @brief 1ステップあたりのシミュレーション内時間
        [[nodiscard]] static double DeltaTime() noexcept;

        /// @brief 2Dとしてシミュレーションするかどうか
        [[nodiscard]] static bool Enable2DMode() noexcept;

        /// @brief フィールドのX方向の半径
        [[nodiscard]] static double FieldRadiusX() noexcept;

        /// @brief フィールドのY方向の半径
        [[nodiscard]] static double FieldRadiusY() noexcept;

        /// @brief フィールドのZ方向の半径
        [[nodiscard]] static double FieldRadiusZ() noexcept;

        /// @brief 総ステップ数
        [[nodiscard]] static uint64_t TotalSteps() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline double Config::Simulation::DeltaTime() noexcept
    {
        return s_deltaTime;
    }

    inline bool Config::Simulation::Enable2DMode() noexcept
    {
        return s_enable2DMode;
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

    inline uint64_t Config::Simulation::TotalSteps() noexcept
    {
        return s_totalSteps;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATION_HPP