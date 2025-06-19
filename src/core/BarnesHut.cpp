#include "BarnesHut.hpp"

BarnesHut::BarnesHut()
{

}

Generator<CellInfo> BarnesHut::iterateAffectableCellInfos(
    [[maybe_unused]] Cell& c,
    [[maybe_unused]] ::std::vector<Cell*> const& cells,
    [[maybe_unused]] const ::std::vector<MoleculeSpace*>& moleculeSpaces
)
{
    co_return;
}
::std::vector<CellInfo> BarnesHut::getAffectableCellInfos(
    [[maybe_unused]] Cell& c,
    [[maybe_unused]] ::std::vector<Cell*> const& cells,
    [[maybe_unused]] const ::std::vector<MoleculeSpace*>& moleculeSpaces
)
{
    return {};
}