#pragma once

#include "CellAlgorithm.hpp"
#include "Cell.hpp"
#include "../UserMoleculeSpace.hpp"
#include <vector>

class CellSimulationModel {
    private:

    protected:
    CellAlgorithm& m_cellAlgorithm;

    constexpr CellSimulationModel(CellAlgorithm& cellAlgorithm) noexcept : m_cellAlgorithm(cellAlgorithm) {}

    virtual ~CellSimulationModel() {}

    public:

    CellSimulationModel(CellSimulationModel const&) = delete;
    CellSimulationModel(CellSimulationModel&&) = delete;    

    CellSimulationModel& operator=(CellSimulationModel const&) = delete;
    CellSimulationModel& operator=(CellSimulationModel&&) = delete;

    virtual void initCells(::std::vector<Cell*>& cells);
    
    virtual Vec3 calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) = 0;

    virtual void beforeNextStep(::std::vector<Cell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces);
    virtual void onNextStep(::std::vector<Cell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces);
};

inline void CellSimulationModel::beforeNextStep(::std::vector<Cell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    m_cellAlgorithm.beforeNextStep(cells, moleculeSpaces);
}

inline void CellSimulationModel::onNextStep(::std::vector<Cell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    m_cellAlgorithm.onNextStep(cells, moleculeSpaces);
}