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
        static inline bool s_enable2dMode;
        static inline double s_fieldRadius;
        static inline int32_t s_imageSize;
        static inline int32_t s_outputInterval;
        static inline uint64_t s_totalSteps;

        public:

        /// @brief 1ステップあたりのシミュレーション内時間
        [[nodiscard]] static double DeltaTime() noexcept;

        /// @brief 2Dとしてシミュレーションするかどうか
        [[nodiscard]] static bool Enable2dMode() noexcept;

        /// @brief フィールドの半径
        [[nodiscard]] static double FieldRadius() noexcept;

        /// @brief フィールドのX方向の半径
        static double FieldRadiusX() noexcept;

        /// @brief フィールドのY方向の半径
        static double FieldRadiusY() noexcept;

        /// @brief フィールドのZ方向の半径
        static double FieldRadiusZ() noexcept;

        /// @brief 出力画像の縦横の長さ
        [[nodiscard]] static int32_t ImageSize() noexcept;

        /// @brief 出力間隔
        [[nodiscard]] static int32_t OutputInterval() noexcept;

        /// @brief 総ステップ数
        [[nodiscard]] static uint64_t TotalSteps() noexcept;

        static void Load(
            ::nlohmann::json& config
        );
    };
}

namespace CellSim::Settings
{
    inline double Config::Simulation::DeltaTime() noexcept
    {
        return s_deltaTime;
    }

    inline bool Config::Simulation::Enable2dMode() noexcept
    {
        return s_enable2dMode;
    }

    inline double Config::Simulation::FieldRadius() noexcept
    {
        return s_fieldRadius;
    }

    inline double Config::Simulation::FieldRadiusX() noexcept
    {
        return s_fieldRadius;
    }

    inline double Config::Simulation::FieldRadiusY() noexcept
    {
        return s_fieldRadius;
    }

    inline double Config::Simulation::FieldRadiusZ() noexcept
    {
        return s_enable2dMode ? 0.0 : s_fieldRadius;
    }

    inline int32_t Config::Simulation::ImageSize() noexcept
    {
        return s_imageSize;
    }

    inline int32_t Config::Simulation::OutputInterval() noexcept
    {
        return s_outputInterval;
    }

    inline uint64_t Config::Simulation::TotalSteps() noexcept
    {
        return s_totalSteps;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATION_HPP