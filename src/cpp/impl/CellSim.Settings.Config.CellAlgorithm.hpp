#ifndef CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_HPP

#include "base.hpp"                                                                                                                                                 
#include "CellSim.Settings.Config.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmType.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::CellAlgorithm final {
        private:

        static inline CellAlgorithms::CellAlgorithmType s_algorithmType;
        static inline bool s_useClusterModel;

        public:

        class CellList;

        CELLSIM_STATIC_CLASS(CellAlgorithm);

        /// @brief 使用するアルゴリズム
        [[nodiscard]] static CellAlgorithms::CellAlgorithmType AlgorithmType() noexcept;

        /// @brief シミュレーションでクラスタモデルを使用するかどうか
        [[nodiscard]] static bool UseClusterModel() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline CellAlgorithms::CellAlgorithmType Config::CellAlgorithm::AlgorithmType() noexcept
    {
        return s_algorithmType;
    }

    inline bool Config::CellAlgorithm::UseClusterModel() noexcept
    {
        return s_useClusterModel;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_HPP