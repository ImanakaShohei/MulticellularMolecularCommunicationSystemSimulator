#pragma once

#include "../UserCell.hpp"
#include "../utils/Vec3.hpp"
#include "../UserMoleculeSpace.hpp"
#include <vector>
#include "CellInfo.hpp"
#include "../threading/Generator.hpp"

class CellAlgorithm {
    private:

    protected:

    CellAlgorithm() = default;
    CellAlgorithm(CellAlgorithm const&) = default;
    CellAlgorithm(CellAlgorithm&&) = default;

    CellAlgorithm& operator=(CellAlgorithm const&) = default;
    CellAlgorithm& operator=(CellAlgorithm&&) = default;

    public:

    constexpr virtual ~CellAlgorithm() {}

    constexpr virtual void beforeNextStep(const ::std::vector<UserCell*>&, const ::std::vector<UserMoleculeSpace*>&) {}
    constexpr virtual void onNextStep(const ::std::vector<UserCell*>&, const ::std::vector<UserMoleculeSpace*>&) {}

    virtual Generator<CellInfo> iterateAffectableCellInfos(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) = 0;
    virtual ::std::vector<CellInfo> getAffectableCellInfos(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces);
};