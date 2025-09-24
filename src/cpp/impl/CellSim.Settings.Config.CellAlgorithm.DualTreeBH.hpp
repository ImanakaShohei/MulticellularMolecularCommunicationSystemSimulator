#ifndef CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_DUALTREEBH_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_DUALTREEBH_HPP

#include "CellSim.Settings.Config.CellAlgorithm.hpp"
#include "base.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::CellAlgorithm::DualTreeBH final {
        private:
        static inline double s_theta;

        public:
        CELLSIM_STATIC_CLASS(DualTreeBH);

        [[nodiscard]] static double Theta() noexcept;

        static void Load(
            ::nlohmann::json const& config
        );
    };
}

namespace CellSim::Settings
{
    inline double Config::CellAlgorithm::DualTreeBH::Theta() noexcept
    {
        return s_theta;
    }
}

#endif //1CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_DUALTREEBH_HPP