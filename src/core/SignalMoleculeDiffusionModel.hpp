#include "CellSimulationModel.hpp"

class SignalMoleculeDiffusionModel : public CellSimulationModel {
    private:
    
    public:

    Vec3 calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) noexcept override { return Vec3::zero(); }

    constexpr SignalMoleculeDiffusionModel(CellAlgorithm& cellAlgorithm) noexcept : CellSimulationModel(cellAlgorithm) {}
};