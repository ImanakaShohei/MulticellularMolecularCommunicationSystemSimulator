#ifndef CELLSIM_CELLALGORITHMS_CELLALGORITHM_HPP
#define CELLSIM_CELLALGORITHMS_CELLALGORITHM_HPP

#include "base.hpp"
#include <vector>

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
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) = 0;

        virtual ::std::vector<Cells::CellInfo> GetAffectableCellInfos(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) const = 0;

        virtual Threading::Generator<Cells::CellInfo> IterateAffectableCellInfos(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) const = 0;

        /// @brief 後処理
        /// @param cells 細胞リスト
        /// @param molecules 分子空間リスト
        virtual void OnAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) = 0;
        
    };
}

#endif //!CELLSIM_CELLALGORITHMS_CELLALGORITHM_HPP