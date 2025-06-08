#include "CellSim.CellAlgorithms.BarnesHut.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmAffectableCellQueryArgs.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmStepArgs.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Threading.Generator.hpp"

namespace CellSim::CellAlgorithms
{
    BarnesHut::BarnesHut()
    {
        // TODO: ここに処理を追加します
    }

    BarnesHut::~BarnesHut()
    {
        // TODO: ここに処理を追加します
    }

    void BarnesHut::BeforeAdvanceStep(
        [[maybe_unused]] const Simulation* sender,
        [[maybe_unused]] CellAlgorithmStepArgs args
    )
    {
        // TODO: ここに処理を追加します
    }

    ::std::vector<Cells::CellInfo> BarnesHut::GetAffectableCellInfos(
        [[maybe_unused]] const Model::CellSimulationModel* sender,
        [[maybe_unused]] CellAlgorithmAffectableCellQueryArgs args
    ) const
    {
        //: ここに処理を追加します
        return {};
    }

    bool BarnesHut::HasMultithreadingSupport() const noexcept
    {
        // TODO: 複数スレッドによる処理ができない場合は'false'にします
        return true;
    }

    Threading::Generator<Cells::CellInfo> BarnesHut::IterateAffectableCellInfos(
        [[maybe_unused]] const Model::CellSimulationModel* sender,
        [[maybe_unused]] CellAlgorithmAffectableCellQueryArgs args
    ) const
    {
        //: ここに処理を追加します
        co_return;
    }

    void BarnesHut::OnAdvanceStep(
        [[maybe_unused]] const Simulation* sender,
        [[maybe_unused]] CellAlgorithmStepArgs args
    )
    {
        // TODO: ここに処理を追加します
    }
}