#ifndef CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_HPP

#include "base.hpp"                                                                                                                                                 
#include "CellSim.Settings.Config.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmType.hpp"

namespace CellSim::Settings
{
    class Config::CellAlgorithm final {
        private:

        static inline CellAlgorithms::CellAlgorithmType s_algorithmType;
        static inline bool s_useClusterModel;

        public:

        CELLSIM_STATIC_CLASS(CellAlgorithm);

        /// @brief 使用するアルゴリズム
        [[nodiscard]] static CellAlgorithms::CellAlgorithmType AlgorithmType() noexcept;

        /// @brief シミュレーションでクラスタモデルを使用するかどうか
        [[nodiscard]] static bool UseClusterModel() noexcept;
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