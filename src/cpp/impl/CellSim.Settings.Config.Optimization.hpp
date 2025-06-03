#ifndef CELLSIM_SETTINGS_CONFIG_OPTIMIZATION_HPP
#define CELLSIM_SETTINGS_CONFIG_OPTIMIZATION_HPP

#include "base.hpp"
#include "CellSim.PeformanceType.hpp"
#include "CellSim.Settings.Config.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    /// @brief 最適化設定
    class Config::Optimization final {
        private:

        static inline PeformanceType s_peformance;

        public:

        CELLSIM_STATIC_CLASS(Optimization);

        /// @brief 実行速度とメモリ使用量の設定
        [[nodiscard]] static PeformanceType Peformance() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline PeformanceType Config::Optimization::Peformance() noexcept
    {
        return s_peformance;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_OPTIMIZATION_HPP