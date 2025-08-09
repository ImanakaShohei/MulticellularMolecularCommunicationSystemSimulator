#include "CellSim.Users.UserMoleculeBehavior.hpp"
#include "impl/CellSim.Containers.Span3.hpp"
#include "impl/CellSim.Numerics.Vector3T.hpp"
#include "impl/CellSim.Molecular.MoleculeBehaviorStepArgs.hpp"
#include "impl/CellSim.Molecular.MoleculeDiffusionArgs.hpp"
#include "impl/CellSim.Molecular.MoleculeInitializationArgs.hpp"

using namespace CellSim;
using namespace CellSim::Cells;
using namespace CellSim::Containers;
using namespace CellSim::Molecular;
using namespace CellSim::Numerics;


namespace CellSim::Users
{
    UserMoleculeBehavior::UserMoleculeBehavior()
    {
        // TODO: ここに処理を追加します
    }

    UserMoleculeBehavior::~UserMoleculeBehavior()
    {
        // TODO: ここに処理を追加します
    }

    void UserMoleculeBehavior::BeforeAdvanceStep(
        [[maybe_unused]] const MoleculeField* sender,
        [[maybe_unused]] MoleculeBehaviorStepArgs args
    )
    {
        // TODO: ここに処理を追加します
    }

    void UserMoleculeBehavior::Diffuse(
        [[maybe_unused]] const MoleculeField* sender,
        [[maybe_unused]] MoleculeDiffusionArgs args
    )
    {
        // TODO: ここに処理を追加します
    }

    void UserMoleculeBehavior::InitializeMolecules(
        [[maybe_unused]] const MoleculeField* sender,
        [[maybe_unused]] MoleculeInitializationArgs args
    )
    {
        // TODO: ここに処理を追加します
    }

    void UserMoleculeBehavior::OnAdvanceStep(
        [[maybe_unused]] const MoleculeField* sender,
        [[maybe_unused]] MoleculeBehaviorStepArgs args
    )
    {
        // TODO: ここに処理を追加します
    }
}