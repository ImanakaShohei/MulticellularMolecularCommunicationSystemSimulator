#ifndef CELLSIM_SETTINGS_CONFIG_MOLECULAR_HPP
#define CELLSIM_SETTINGS_CONFIG_MOLECULAR_HPP

#include "base.hpp"
#include "CellSim.Molecular.MoleculeCreateInfo.hpp"
#include "CellSim.Settings.Config.hpp"

#include <vector>
#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    /// @brief 分子設定
    class Config::Molecular final {
        private:

        static inline ::std::vector<::CellSim::Molecular::MoleculeCreateInfo> s_molecularConfigs;

        public:

        class Behavior;

        CELLSIM_STATIC_CLASS(Molecular);

        /// @brief 
        [[nodiscard]]
        static
        ::std::vector<::CellSim::Molecular::MoleculeCreateInfo> const&
        MolecularConfigs() noexcept;

        static void Load(
            ::nlohmann::json& config
        );
    };
}

namespace CellSim::Settings
{
    inline
    ::std::vector<::CellSim::Molecular::MoleculeCreateInfo> const&
    Config::Molecular::MolecularConfigs() noexcept
    {
        return s_molecularConfigs;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_MOLECULAR_HPP