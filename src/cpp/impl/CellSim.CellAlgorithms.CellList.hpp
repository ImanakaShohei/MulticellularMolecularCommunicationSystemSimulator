#ifndef CELLSIM_CELLALGORITHMS_CELLLIST_HPP
#define CELLSIM_CELLALGORITHMS_CELLLIST_HPP

#include "base.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Containers.Span3.hpp"

#include <vector>

namespace CellSim::CellAlgorithms
{
    /// @brief Cell-List
    class CellList : public CellAlgorithm {
        private:

        ::std::vector<::std::vector<Cells::CellInfo>> m_cellField;

        size_t m_gridCountX;
        size_t m_gridCountY;
        size_t m_gridCountZ;

        double m_searchRadius;

        Containers::Span3<::std::vector<Cells::CellInfo>> m_span;

        double m_squareSeachRadius;

        public:
        
        CellList();

        CellList(
            size_t gridCountX,
            size_t gridCountY,
            size_t gridCountZ,
            double searchRadius
        );

        CellList(CellList const&) = delete;

        ~CellList();

        CellList& operator=(CellList const&) = delete;

        void BeforeAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) override;

        ::std::vector<Cells::CellInfo> GetAffectableCellInfos(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) const override;

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

#endif //!CELLSIM_CELLALGORITHMS_CELLLIST_HPP