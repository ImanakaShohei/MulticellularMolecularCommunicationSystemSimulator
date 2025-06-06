#ifndef CELLSIM_CELLALGORITHMS_CELLALGORITHM_HPP
#define CELLSIM_CELLALGORITHMS_CELLALGORITHM_HPP

#include "base.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
#include "CellSim.Settings.Config.Optimization.hpp"
#include "CellSim.Threading.Generator.hpp"
#include <vector>

#define CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE(cellInfo, cellAlgorithm, target, cells, molecules, func)              \
    switch (::CellSim::Settings::Config::Optimization::Peformance()) {                                                     \
        case ::CellSim::PeformanceType::Fast:                                                                              \
        for (::CellSim::Cells::CellInfo& cellInfo : (cellAlgorithm).GetAffectableCellInfos(target, cells, molecules)) {    \
            func                                                                                                           \
        }                                                                                                                  \
        break;                                                                                                             \
        case ::CellSim::PeformanceType::LowMemory:                                                                         \
        for (::CellSim::Cells::CellInfo cellInfo : (cellAlgorithm).IterateAffectableCellInfos(target, cells, molecules)) { \
            func                                                                                                           \
        }                                                                                                                  \
        break;                                                                                                             \
    }

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
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) = 0;

        /// @brief ターゲットの細胞かける力を計算
        /// @param target ターゲットの細胞
        /// @param cells 細胞リスト
        /// @param moleculeSpaces 分子空間リスト
        /// @param cellAlgorithm 高速化アルゴリズム
        /// @return 計算結果
        /// @note この関数はOverrideForceComputation()が'true'のときに呼ばれます
        [[nodiscard]] virtual Numerics::Vector3 ComputeForceOnCell(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) const;

        virtual ::std::vector<Cells::CellInfo> GetAffectableCellInfos(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) const = 0;

        virtual Threading::Generator<Cells::CellInfo> IterateAffectableCellInfos(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) const = 0;

        /// @brief 後処理
        /// @param cells 細胞リスト
        /// @param molecules 分子空間リスト
        virtual void OnAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) = 0;

        /// @brief アルゴリズム側で力の計算をすることを強制するフラグ
        [[nodiscard]] virtual constexpr bool OverrideForceComputation() const noexcept;
        
    };
}

namespace CellSim::CellAlgorithms
{
    Numerics::Vector3 CellAlgorithm::ComputeForceOnCell(
        Cells::Cell const& target,
        ::std::vector<Cells::Cell> const& cells,
        ::std::vector<Molecular::MoleculeField> const& moleculeSpaces
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