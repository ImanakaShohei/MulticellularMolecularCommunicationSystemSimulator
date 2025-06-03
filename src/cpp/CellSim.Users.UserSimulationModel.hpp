#ifndef CELLSIM_USERS_USERCELLSIMULATIONMODEL_HPP
#define CELLSIM_USERS_USERCELLSIMULATIONMODEL_HPP

#include "impl/base.hpp"
#include "impl/CellSim.Model.CellSimulationModel.hpp"

namespace CellSim::Users
{
    /// @brief ユーザー定義力学モデル
    class UserSimulationModel : public Model::CellSimulationModel {
        public:

        UserSimulationModel();
        ~UserSimulationModel();

        void BeforeAdvanceStep(
            ::std::vector<Cells::Cell>& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) override;

        Numerics::Vector3 ComputeForceOnCell(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& moleculeSpaces,
            CellAlgorithms::CellAlgorithm const& cellAlgorithm
        ) const override;

        void InitializeCells(::std::vector<Cells::Cell>& cells) override;

        void OnAdvanceStep(
            ::std::vector<Cells::Cell>& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) override;

        bool UseCellAlgorithm() const noexcept override;
    };
}

#endif //!CELLSIM_USERS_USERCELLSIMULATIONMODEL_HPP