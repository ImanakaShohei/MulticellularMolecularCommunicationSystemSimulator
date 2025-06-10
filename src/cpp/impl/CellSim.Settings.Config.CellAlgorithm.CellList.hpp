#ifndef CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_CELLLIST_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_CELLLIST_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::CellAlgorithm::CellList final {
        private:

        static inline size_t s_gridCountX;
        static inline size_t s_gridCountY;
        static inline size_t s_gridCountZ;
        static inline double s_searchRadius;
        
        public:

        CELLSIM_STATIC_CLASS(CellList);

        [[nodiscard]] static size_t GridCountX() noexcept;
        [[nodiscard]] static size_t GridCountY() noexcept;
        [[nodiscard]] static size_t GridCountZ() noexcept;

        /// @brief 探索範囲
        [[nodiscard]] static double SearchRadius() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline size_t Config::CellAlgorithm::CellList::GridCountX() noexcept
    {
        return s_gridCountX;
    }

    inline size_t Config::CellAlgorithm::CellList::GridCountY() noexcept
    {
        return s_gridCountY;
    }

    inline size_t Config::CellAlgorithm::CellList::GridCountZ() noexcept
    {
        return s_gridCountZ;
    }

    inline double Config::CellAlgorithm::CellList::SearchRadius() noexcept
    {
        return s_searchRadius;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_CELLLIST_HPP