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

    Generator<CellInfo> iterateAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
    ::std::vector<CellInfo> getAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
};