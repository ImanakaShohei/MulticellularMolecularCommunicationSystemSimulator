#pragma once

#include "../SimulationSettings.hpp"
#include "../UserCell.hpp"
#include "../utils/Util.hpp"
#include "../utils/Vec3.hpp"
#include "CellList.hpp"

class ClusterModel final {
    public:

    ClusterModel() = delete;
    ClusterModel(ClusterModel const&) = delete;
    ClusterModel(ClusterModel&&) = delete;

    ClusterModel& operator=(ClusterModel const&) = delete;
    ClusterModel& operator=(ClusterModel&&) = delete;

    static void combine(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces);
    static void combine(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces, CellList& cellList);
    static void combine(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces, CellList* pCellList);
    static void combine(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces, ::std::nullptr_t);
};

inline void ClusterModel::combine(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces, ::std::nullptr_t)
{
    combine(cells, moleculeSpaces);
}