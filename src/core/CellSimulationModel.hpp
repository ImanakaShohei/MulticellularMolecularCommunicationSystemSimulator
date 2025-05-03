#pragma once

#include "CellAlgorithm.hpp"
#include "../UserCell.hpp"
#include "../UserMoleculeSpace.hpp"
#include <vector>

class CellSimulationModel {
    protected:
    CellAlgorithm& m_cellAlgorithm;

    constexpr CellSimulationModel(CellAlgorithm& cellAlgorithm) noexcept : m_cellAlgorithm(cellAlgorithm) {}
    CellSimulationModel(CellSimulationModel const&) = default;
    CellSimulationModel(CellSimulationModel&&) = default;

    virtual ~CellSimulationModel() {}

    CellSimulationModel& operator=(CellSimulationModel const&) = default;
    CellSimulationModel& operator=(CellSimulationModel&&) = default;

    public:

    virtual void initCells(::std::vector<UserCell*>& cells);
    
    virtual Vec3 calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces);

    virtual void beforeNextStep(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces);
    virtual void onNextStep(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces);
};

inline Vec3 CellSimulationModel::calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    return m_cellAlgorithm.calcCellForce(c, cells, moleculeSpaces);
}

inline void CellSimulationModel::beforeNextStep(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    m_cellAlgorithm.beforeNextStep(cells, moleculeSpaces);
}

inline void CellSimulationModel::onNextStep(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    m_cellAlgorithm.onNextStep(cells, moleculeSpaces);
}