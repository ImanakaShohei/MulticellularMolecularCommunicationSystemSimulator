#pragma once

#include "../SimulationSettings.hpp"
#include "../UserCell.hpp"
#include "../utils/Util.hpp"
#include "../utils/Vec3.hpp"
#include "CellAlgorithm.hpp"

class Cluster : public CellAlgorithm {
    private:

    public:

    Vec3 calcCellForce(const ::std::shared_ptr<UserCell>& c, ::std::vector<::std::shared_ptr<UserCell>> const& cells, const ::std::vector<::std::unique_ptr<UserMoleculeSpace>>&) noexcept override;
    void beforeNextStep(const ::std::vector<::std::shared_ptr<UserCell>>& cells, const ::std::vector<::std::unique_ptr<UserMoleculeSpace>>&) override;
};