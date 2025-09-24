#ifndef CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_CELLLIST_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_CELLLIST_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::CellAlgorithm::CellList final {
        private:

        static inline size_t s_gridCount;
        static inline double s_searchRadius;
        
        public:

        CELLSIM_STATIC_CLASS(CellList);

        [[nodiscard]] static size_t GridCount() noexcept;

        /// @brief 探索範囲
        [[nodiscard]] static double SearchRadius() noexcept;

        static void Load(
            ::nlohmann::json const& config
        );
    };
}

namespace CellSim::Settings
{
    inline size_t Config::CellAlgorithm::CellList::GridCount() noexcept
    {
        return s_gridCount;
    }

    inline double Config::CellAlgorithm::CellList::SearchRadius() noexcept
    {
        return s_searchRadius;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_CELLLIST_HPP