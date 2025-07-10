#include "CellSim.CellAlgorithms.NaiveAlgorithm.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmAffectableCellQueryArgs.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"
#include "CellSim.Model.SimulationModelForceComputationArgs.hpp"
#include "CellSim.Threading.Generator.hpp"

namespace CellSim::CellAlgorithms
{
    Numerics::Vector3 NaiveAlgorithm::ComputeForceOnCell(
        const Simulation* sender,
        CellAlgorithmForceComputationArgs args
    ) const
    {
        return args.SimulationModel->ComputeForceOnCell(
            sender,
            { args.Target, args.Cells, args.Cells, args.Fields, nullptr }
        );
    }

    ::std::vector<Cells::CellInfo> NaiveAlgorithm::GetAffectableCellInfos(
        const Model::CellSimulationModel*,
        CellAlgorithmAffectableCellQueryArgs args
    ) const
    {
        ::std::vector<Cells::CellInfo> vec;

        if (args.Cells->size() > 0) [[likely]] vec.reserve(args.Cells->size() - 1);

        for (Cells::Cell const& cell : *args.Cells) {
            if (&cell == args.Target) continue;
            vec.emplace_back(cell);
        }

        return vec;
    }

    Threading::Generator<Cells::CellInfo> NaiveAlgorithm::IterateAffectableCellInfos(
        const Model::CellSimulationModel*,
        CellAlgorithmAffectableCellQueryArgs args
    ) const
    {
        for (Cells::Cell const& cell : *args.Cells) {
            if (&cell == args.Target) continue;
            co_yield cell;
        }
    }
}