#include "CellSim.Users.UserCellAlgorithm.hpp"
#include "impl/CellSim.CellAlgorithms.CellAlgorithmAffectableCellQueryArgs.hpp"
#include "impl/CellSim.CellAlgorithms.CellAlgorithmStepArgs.hpp"
#include "impl/CellSim.Cells.CellInfo.hpp"
#include "impl/CellSim.Threading.Generator.hpp"

using namespace CellSim;
using namespace CellSim::CellAlgorithms;
using namespace CellSim::Cells;
using namespace CellSim::Model;
using namespace CellSim::Molecular;
using namespace CellSim::Threading;

namespace CellSim::Users
{

    UserCellAlgorithm::UserCellAlgorithm()
    {
        // TODO: ここに処理を追加します
    }

    UserCellAlgorithm::~UserCellAlgorithm()
    {
        // TODO: ここに処理を追加します
    }

    void UserCellAlgorithm::BeforeAdvanceStep(
        [[maybe_unused]] const Simulation* sender,
        [[maybe_unused]] CellAlgorithmStepArgs args
    )
    {
        // TODO: ここに処理を追加します
    }

    ::std::vector<CellInfo> UserCellAlgorithm::GetAffectableCellInfos(
        [[maybe_unused]] const CellSimulationModel* sender,
        [[maybe_unused]] CellAlgorithmAffectableCellQueryArgs args
    ) const
    {
        //: ここに処理を追加します
        return {};
    }

    bool UserCellAlgorithm::HasMultithreadingSupport() const noexcept
    {
        // TODO: 複数スレッドによる処理ができない場合は'false'にします
        return true;
    }

    Generator<CellInfo> UserCellAlgorithm::IterateAffectableCellInfos(
        [[maybe_unused]] const CellSimulationModel* sender,
        [[maybe_unused]] CellAlgorithmAffectableCellQueryArgs args
    ) const
    {
        //: ここに処理を追加します
        co_return;
    }

    void UserCellAlgorithm::OnAdvanceStep(
        [[maybe_unused]] const Simulation* sender,
        [[maybe_unused]] CellAlgorithmStepArgs args
    )
    {
        // TODO: ここに処理を追加します
    }
}