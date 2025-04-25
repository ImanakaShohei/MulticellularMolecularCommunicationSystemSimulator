#pragma once

#include "../SimulationSettings.hpp"
#include "../UserCell.hpp"
#include "../utils/Util.hpp"
#include "../utils/Vec3.hpp"
#include "CellAlgorithm.hpp"
#include <memory>
#include <vector>

class NaiveAlgorithm : public CellAlgorithm {
    public:

    Vec3 calcCellForce(const ::std::shared_ptr<UserCell>& c, ::std::vector<::std::shared_ptr<UserCell>> const& cells, const ::std::vector<::std::unique_ptr<UserMoleculeSpace>>&) noexcept override;
};