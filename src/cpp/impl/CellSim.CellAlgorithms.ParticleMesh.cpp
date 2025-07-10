#include "CellSim.CellAlgorithms.ParticleMesh.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmAffectableCellQueryArgs.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmStepArgs.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"
#include "CellSim.Model.SimulationModelForceComputationArgs.hpp"
#include "CellSim.Threading.Generator.hpp"

namespace CellSim::CellAlgorithms
{
    ParticleMesh::ParticleMesh()
    {
        // TODO: ここに処理を追加します
    }

    ParticleMesh::~ParticleMesh()
    {
        // TODO: ここに処理を追加します
    }

    void ParticleMesh::BeforeAdvanceStep(
        [[maybe_unused]] const Simulation* sender,
        [[maybe_unused]] CellAlgorithmStepArgs args
    )
    {
        // TODO: ここに処理を追加します
    }

    Numerics::Vector3 ParticleMesh::ComputeForceOnCell(
        [[maybe_unused]] const Simulation* sender,
        [[maybe_unused]] CellAlgorithmForceComputationArgs args
    ) const
    {
        // TODO: 処理の内容を変更します
        return args.SimulationModel->ComputeForceOnCell(
            sender,
            { args.Target, args.Cells, args.Fields, nullptr }
        );
    }

    ::std::vector<Cells::CellInfo> ParticleMesh::GetAffectableCellInfos(
        [[maybe_unused]] const Model::CellSimulationModel* sender,
        [[maybe_unused]] CellAlgorithmAffectableCellQueryArgs args
    ) const
    {
        //: ここに処理を追加します
        return {};
    }

    bool ParticleMesh::HasMultithreadingSupport() const noexcept
    {
        // TODO: 複数スレッドによる処理ができない場合は'false'にします
        return true;
    }

    Threading::Generator<Cells::CellInfo> ParticleMesh::IterateAffectableCellInfos(
        [[maybe_unused]] const Model::CellSimulationModel* sender,
        [[maybe_unused]] CellAlgorithmAffectableCellQueryArgs args
    ) const
    {
        //: ここに処理を追加します
        co_return;
    }

    void ParticleMesh::OnAdvanceStep(
        [[maybe_unused]] const Simulation* sender,
        [[maybe_unused]] CellAlgorithmStepArgs args
    )
    {
        // TODO: ここに処理を追加します
    }

    bool ParticleMesh::OverrideForceComputation() const noexcept
    {
        // 'true'にすることでアルゴリズム側で相互作用を計算します
        return true;
    }
}