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

        static inline uint32_t s_maxDegreeOfParallelism;
        static inline PeformanceType s_peformance;
        
        public:

        CELLSIM_STATIC_CLASS(Optimization);

        /// @brief 
        [[nodiscard]] static uint32_t MaxDegreeOfParallelism() noexcept;

        /// @brief 実行速度とメモリ使用量の設定
        [[nodiscard]] static PeformanceType Peformance() noexcept;

        static void Load(
            ::nlohmann::json& config
        );
    };
}

namespace CellSim::Settings
{
    inline uint32_t Config::Optimization::MaxDegreeOfParallelism() noexcept
    {
        return s_maxDegreeOfParallelism;
    }

    inline PeformanceType Config::Optimization::Peformance() noexcept
    {
        return s_peformance;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_OPTIMIZATION_HPP