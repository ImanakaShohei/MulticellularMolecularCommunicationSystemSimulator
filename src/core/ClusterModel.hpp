#pragma once

#include "../SimulationSettings.hpp"
#include "../UserCell.hpp"
#include "../utils/Util.hpp"
#include "../utils/Vec3.hpp"
#include "CellAlgorithm.hpp"

class ClusterModel final {
    public:

    ClusterModel() = delete;
    ClusterModel(ClusterModel const&) = delete;
    ClusterModel(ClusterModel&&) = delete;

    static void onNextStep(const ::std::vector<UserCell*>& cells);
};