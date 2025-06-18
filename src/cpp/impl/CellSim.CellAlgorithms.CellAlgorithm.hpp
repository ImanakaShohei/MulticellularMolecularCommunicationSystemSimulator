#ifndef CELLSIM_CELLALGORITHMS_CELLALGORITHM_HPP
#define CELLSIM_CELLALGORITHMS_CELLALGORITHM_HPP

#include "base.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmForceComputationArgs.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
#include "CellSim.Settings.Config.Optimization.hpp"
#include "CellSim.Threading.Generator.hpp"
#include <vector>

#define CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE_EX(cellInfo, cellAlgorithm, sender, target, cells, molecules, func)               \
    switch (::CellSim::Settings::Config::Optimization::Peformance()) {                                                                 \
        case ::CellSim::PeformanceType::Fast:                                                                                          \
        for (::CellSim::Cells::CellInfo cellInfo : (cellAlgorithm).GetAffectableCellInfos(sender, { target, cells, molecules })) {     \
            func                                                                                                                       \
        }                                                                                                                              \
        break;                                                                                                                         \
        case ::CellSim::PeformanceType::LowMemory:                                                                                     \
        for (::CellSim::Cells::CellInfo cellInfo : (cellAlgorithm).IterateAffectableCellInfos(sender, { target, cells, molecules })) { \
            func                                                                                                                       \
        }                                                                                                                              \
        break;                                                                                                                         \
    }

#define CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE(cellInfo, cellAlgorithm, target, cells, molecules, func)     \
    CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE_EX(cellInfo, cellAlgorithm, this, target, cells, molecules, func)

namespace CellSim::CellAlgorithms
{
    /// @brief 高速化アルゴリズム
    class CellAlgorithm {
        public:

        /// @brief CellAlgorithmTypeからインスタンスを作成
        /// @param type 種類
        /// @return インスタンス
        [[nodiscard]] static CellAlgorithm* FromType(CellAlgorithmType type);

        constexpr virtual ~CellAlgorithm() {}

        /// @brief 前処理
        /// @param cells 細胞リスト
        /// @param molecules 分子空間リスト
        virtual void BeforeAdvanceStep(
            const Simulation* sender,
            CellAlgorithmStepArgs args
        ) = 0;

        /// @brief ターゲットの細胞かける力を計算
        /// @param target ターゲットの細胞
        /// @param cells 細胞リスト
        /// @param moleculeSpaces 分子空間リスト
        /// @param cellAlgorithm 高速化アルゴリズム
        /// @return 計算結果
        /// @note この関数はOverrideForceComputation()が'true'のときに呼ばれます
        [[nodiscard]] virtual Numerics::Vector3 ComputeForceOnCell(
            const Simulation* sender,
            CellAlgorithmForceComputationArgs args
        ) const;

        virtual ::std::vector<Cells::CellInfo> GetAffectableCellInfos(
            const Model::CellSimulationModel* sender,
            CellAlgorithmAffectableCellQueryArgs args
        ) const = 0;

        /// @brief このアルゴリズムが複数スレッドによる処理をサポートしているかどうか
        virtual bool HasMultithreadingSupport() const noexcept = 0;

        virtual Threading::Generator<Cells::CellInfo> IterateAffectableCellInfos(
            const Model::CellSimulationModel* sender,
            CellAlgorithmAffectableCellQueryArgs args
        ) const = 0;

        /// @brief 後処理
        /// @param cells 細胞リスト
        /// @param molecules 分子空間リスト
        virtual void OnAdvanceStep(
            const Simulation* sender,
            CellAlgorithmStepArgs args
        ) = 0;

        /// @brief アルゴリズム側で力の計算をすることを強制するフラグ
        [[nodiscard]] virtual constexpr bool OverrideForceComputation() const noexcept;
        
    };
}

namespace CellSim::CellAlgorithms
{
    inline Numerics::Vector3 CellAlgorithm::ComputeForceOnCell(
        const Simulation* sender,
        CellAlgorithmForceComputationArgs args
    ) const
    {
        return Numerics::Vector3();
    }

    constexpr bool CellAlgorithm::OverrideForceComputation() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_CELLALGORITHMS_CELLALGORITHM_HPP