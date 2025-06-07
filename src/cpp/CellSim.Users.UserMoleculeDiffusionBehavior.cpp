#include "CellSim.Users.UserMoleculeDiffusionBehavior.hpp"
#include "impl/CellSim.Containers.Span3.hpp"
#include "impl/CellSim.Numerics.Vector3T.hpp"

using namespace CellSim;
using namespace CellSim::Cells;
using namespace CellSim::Containers;
using namespace CellSim::Molecular;
using namespace CellSim::Numerics;


namespace CellSim::Users
{
    UserMoleculeDiffusionBehavior::UserMoleculeDiffusionBehavior()
    {
        // TODO: ここに処理を追加します
    }

    UserMoleculeDiffusionBehavior::~UserMoleculeDiffusionBehavior()
    {
        // TODO: ここに処理を追加します
    }

    void UserMoleculeDiffusionBehavior::BeforeAdvanceStep(
        [[maybe_unused]] ::std::vector<Cell> const& cells,
        [[maybe_unused]] MoleculeField const& field
    )
    {
        // TODO: ここに処理を追加します
    }

    void UserMoleculeDiffusionBehavior::Diffuse(
        [[maybe_unused]] Span3<double> concentrations,
        [[maybe_unused]] MoleculeField const& field
    )
    {
        // TODO: ここに処理を追加します
    }

    void UserMoleculeDiffusionBehavior::OnAdvanceStep(
        [[maybe_unused]] ::std::vector<Cell> const& cells,
        [[maybe_unused]] MoleculeField const& field
    )
    {
        // TODO: ここに処理を追加します
    }
}