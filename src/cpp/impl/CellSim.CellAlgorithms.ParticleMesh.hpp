#ifndef CELLSIM_CELLALGORITHMS_PARTICLEMESH_HPP
#define CELLSIM_CELLALGORITHMS_PARTICLEMESH_HPP

#include "base.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"

namespace CellSim::CellAlgorithms
{
    /// @brief PM法
    class ParticleMesh : public CellAlgorithm {
        private:

        // TODO: ここにメンバーを追加します

        public:

        // 引数を追加してはいけない
        ParticleMesh();
        ~ParticleMesh();

        void BeforeAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) override;

        ::std::vector<Cells::CellInfo> GetAffectableCellInfos(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) const override;

        bool HasMultithreadingSupport() const noexcept override;

        Threading::Generator<Cells::CellInfo> IterateAffectableCellInfos(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) const override;

        void OnAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) override;
    };
}

#endif //!CELLSIM_CELLALGORITHMS_PARTICLEMESH_HPP