#ifndef CELLSIM_SETTINGS_CONFIG_MOLECULAR_HPP
#define CELLSIM_SETTINGS_CONFIG_MOLECULAR_HPP

#include "base.hpp"
#include "CellSim.Molecular.BoundaryCondition.hpp"
#include "CellSim.Molecular.InitialMoleculeDistribution.hpp"
#include "CellSim.Settings.Config.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    /// @brief 分子設定
    class Config::Molecular final {
        private:

        static inline ::CellSim::Molecular::BoundaryCondition s_boundaryCondition;
        static inline ::CellSim::Molecular::InitialMoleculeDistribution s_initialDistribution;

        public:

        CELLSIM_STATIC_CLASS(Molecular);

        /// @brief 境界条件
        [[nodiscard]] static ::CellSim::Molecular::BoundaryCondition BoundaryCondition() noexcept;

        /// @brief 初期配置
        [[nodiscard]] static ::CellSim::Molecular::InitialMoleculeDistribution InitialDistribution() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline ::CellSim::Molecular::BoundaryCondition Config::Molecular::BoundaryCondition() noexcept
    {
        return s_boundaryCondition;
    }

    inline ::CellSim::Molecular::InitialMoleculeDistribution Config::Molecular::InitialDistribution() noexcept
    {
        return s_initialDistribution;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_MOLECULAR_HPP