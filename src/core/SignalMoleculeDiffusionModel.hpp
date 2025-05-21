#include "CellSimulationModel.hpp"

class SignalMoleculeDiffusionModel : public CellSimulationModel {
    private:
    
    public:

    constexpr SignalMoleculeDiffusionModel(CellAlgorithm& cellAlgorithm) noexcept : CellSimulationModel(cellAlgorithm) {}

    constexpr Vec3 calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) noexcept override;
    void onNextStep(::std::vector<Cell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
};

constexpr Vec3 SignalMoleculeDiffusionModel::calcCellForce(Cell&, ::std::vector<Cell*> const&, const ::std::vector<UserMoleculeSpace*>&) noexcept
{
    return Vec3::zero();
}