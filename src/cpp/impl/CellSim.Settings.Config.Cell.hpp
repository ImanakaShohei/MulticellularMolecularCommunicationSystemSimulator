#ifndef CELLSIM_SETTINGS_CONFIG_CELL_HPP
#define CELLSIM_SETTINGS_CONFIG_CELL_HPP

#include "base.hpp"
#include "CellSim.Cells.CellBehaviorType.hpp"
#include "CellSim.Settings.Config.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    /// @brief 細胞設定
    class Config::Cell final {
        private:

        static inline Cells::CellBehaviorType s_behaviorType;
        static inline size_t s_cellCount;
        static inline bool s_enableGrowth;
        static inline double s_growthRate;
        static inline double s_radius;

        public:

        CELLSIM_STATIC_CLASS(Cell);

        // プロパティ

        /// @brief 細胞のふるまい
        [[nodiscard]] static Cells::CellBehaviorType BehaviorType() noexcept;

        /// @brief 細胞の初期数
        [[nodiscard]] static size_t CellCount() noexcept;

        /// @brief 細胞の成長・分裂を有効にするかどうか
        [[nodiscard]] static bool EnableGrowth() noexcept;

        /// @brief 細胞の成長速度
        [[nodiscard]] static double GrowthRate() noexcept;

        /// @brief 細胞の初期半径
        [[nodiscard]] static double Radius() noexcept;

        // メソッド

        static void Load(::nlohmann::json const& cellConfig);
    };
}

namespace CellSim::Settings
{
    inline Cells::CellBehaviorType Config::Cell::BehaviorType() noexcept
    {
        return s_behaviorType;
    }

    inline size_t Config::Cell::CellCount() noexcept
    {
        return s_cellCount;
    }

    inline bool Config::Cell::EnableGrowth() noexcept
    {
        return s_enableGrowth;
    }

    inline double Config::Cell::GrowthRate() noexcept
    {
        return s_growthRate;
    }

    inline double Config::Cell::Radius() noexcept
    {
        return s_radius;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_CELL_HPP