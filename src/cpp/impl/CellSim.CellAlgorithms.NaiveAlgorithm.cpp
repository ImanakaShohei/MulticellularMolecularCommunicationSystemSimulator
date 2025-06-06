#include "CellSim.CellAlgorithms.NaiveAlgorithm.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Threading.Generator.hpp"

namespace CellSim::CellAlgorithms
{
    ::std::vector<Cells::CellInfo> NaiveAlgorithm::GetAffectableCellInfos(
        Cells::Cell const& target,
        ::std::vector<Cells::Cell> const& cells,
        ::std::vector<Molecular::MoleculeField> const&
    ) const
    {
        ::std::vector<Cells::CellInfo> vec;
        if (cells.size() > 0) [[likely]] vec.reserve(cells.size() - 1);
        const Cells::Cell* pTarget = &target;
        for (Cells::Cell const& cell : cells) {
            if (&cell == pTarget) continue;
            vec.push_back(cell);
        }

        return vec;
    }

    Threading::Generator<Cells::CellInfo> NaiveAlgorithm::IterateAffectableCellInfos(
        Cells::Cell const& target,
        ::std::vector<Cells::Cell> const& cells,
        ::std::vector<Molecular::MoleculeField> const&
    ) const
    {
        const Cells::Cell* pTarget = &target;
        
        for (Cells::Cell const& cell : cells) {
            if (&cell == pTarget) continue;
            co_yield cell;
        }
    }
}