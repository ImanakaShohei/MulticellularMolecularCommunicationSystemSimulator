#pragma once

#include "Cell.hpp"
#include "../utils/Vec3.hpp"
#include "CellList.hpp"
#include "MoleculeSpace.hpp"

class ClusterModel final {
    public:

    ClusterModel() = delete;
    ClusterModel(ClusterModel const&) = delete;
    ClusterModel(ClusterModel&&) = delete;

    ClusterModel& operator=(ClusterModel const&) = delete;
    ClusterModel& operator=(ClusterModel&&) = delete;

    static void combine(const ::std::vector<Cell*>& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces);
    static void combine(const ::std::vector<Cell*>& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces, CellList& cellList);
    static void combine(const ::std::vector<Cell*>& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces, CellList* pCellList);
    static void combine(const ::std::vector<Cell*>& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces, ::std::nullptr_t);
};

inline void ClusterModel::combine(const ::std::vector<Cell*>& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces, ::std::nullptr_t)
{
    combine(cells, moleculeSpaces);
}