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

    static void onNextStep(const ::std::vector<UserCell*>& cells);
    static void onNextStep(const ::std::vector<UserCell*>& cells, CellList const& cellList);
    static void onNextStep(const ::std::vector<UserCell*>& cells, const CellList* pCellList);
    static void onNextStep(const ::std::vector<UserCell*>& cells, ::std::nullptr_t);
};

inline void ClusterModel::onNextStep(const ::std::vector<UserCell*>& cells, ::std::nullptr_t)
{
    onNextStep(cells);
}