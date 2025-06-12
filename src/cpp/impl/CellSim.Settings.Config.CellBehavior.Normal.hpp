#ifndef CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_NORMAL_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_NORMAL_HPP

#include "base.hpp"
#include "CellSim.Cells.CellBehaviorType.hpp"
#include "CellSim.Settings.Config.CellBehavior.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::CellBehavior::Normal final {
        private:

        static inline double s_cellDivisionRadius;

        public:

        CELLSIM_STATIC_CLASS(Normal);

        /// @brief 細胞の半径がこの値を超えると分裂する
        /// @return 
        [[nodiscard]] static double CellDivisionRadius() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    double Config::CellBehavior::Normal::CellDivisionRadius() noexcept
    {
        return s_cellDivisionRadius;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_NORMAL_HPP