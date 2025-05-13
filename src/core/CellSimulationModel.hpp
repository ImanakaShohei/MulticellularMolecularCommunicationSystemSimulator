#pragma once

#include "CellAlgorithm.hpp"
#include "../UserCell.hpp"
#include "../UserMoleculeSpace.hpp"
#include <vector>

class CellSimulationModel {
    private:
    CellAlgorithm& m_cellAlgorithm;

    protected:

    constexpr CellSimulationModel(CellAlgorithm& cellAlgorithm) noexcept : m_cellAlgorithm(cellAlgorithm) {}

    virtual ~CellSimulationModel() {}

    public:

    CellSimulationModel(CellSimulationModel const&) = delete;
    CellSimulationModel(CellSimulationModel&&) = delete;    

    CellSimulationModel& operator=(CellSimulationModel const&) = delete;
    CellSimulationModel& operator=(CellSimulationModel&&) = delete;

    virtual void initCells(::std::vector<UserCell*>& cells);
    
    virtual Vec3 calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces);

    virtual void beforeNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces);
    virtual void onNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces);
};

inline Vec3 CellSimulationModel::calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    return m_cellAlgorithm.calcCellForce(c, cells, moleculeSpaces);
}

inline void CellSimulationModel::beforeNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    m_cellAlgorithm.beforeNextStep(cells, moleculeSpaces);
}

inline void CellSimulationModel::onNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    m_cellAlgorithm.onNextStep(cells, moleculeSpaces);
}