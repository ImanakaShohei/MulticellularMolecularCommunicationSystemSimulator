#include "CellSim.Model.NetworkFormationModel.hpp"
#include "CellSim.Model.SimulationModelForceComputationArgs.hpp"
#include "CellSim.Model.SimulationModelStepArgs.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmAffectableCellQueryArgs.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"
#include "CellSim.Settings.Config.SimulationModel.NetworkFormation.hpp"
#include "CellSim.Threading.ThreadPool.hpp"

#include "CellSim.Messages.hpp"

#include <stdexcept>

namespace CellSim::Model
{
    NetworkFormationModel::NetworkFormationModel()
        : NetworkFormationModel(
            Settings::Config::SimulationModel::NetworkFormation::AdhesiveRepulsionFactor(),
            Settings::Config::SimulationModel::NetworkFormation::AttractionFactor(),
            Settings::Config::SimulationModel::NetworkFormation::Lambda(),
            Settings::Config::SimulationModel::NetworkFormation::MaxAttractionDistance(),
            Settings::Config::SimulationModel::NetworkFormation::MaxRepulsionDistance(),
            Settings::Config::SimulationModel::NetworkFormation::MinAttractionDistance(),
            Settings::Config::SimulationModel::NetworkFormation::RemoteForceFactor()
        )
    {
    }

    NetworkFormationModel::NetworkFormationModel(
        double adhesiveRepulsionFactor,
        double attractionFactor,
        double lambda,
        double maxAttractionDistance,
        double maxRepulsionDistance,
        double minAttractionDistance,
        double remoteForceFactor
    )
    : m_adhesiveRepulsionFactor(adhesiveRepulsionFactor)
    , m_attractionFactor(attractionFactor)
    , m_lambda(lambda)
    , m_maxAttractionDistance(maxAttractionDistance)
    , m_maxRepulsionDistance(maxRepulsionDistance)
    , m_minAttractionDistance(minAttractionDistance)
    , m_remoteForceFactor(remoteForceFactor)
    , m_reverseLambda(1.0 / lambda)
    , m_squareMaxAttractionDistance(maxAttractionDistance * maxAttractionDistance)
    , m_cellList(
        (size_t)(Settings::Config::Simulation::FieldRadius() / maxAttractionDistance) + 1,
        Settings::Config::Simulation::Enable2DMode(),
        maxAttractionDistance
    )
    {
        if (adhesiveRepulsionFactor < 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Model.NetworkFormationModel.NetworkFormationModel.Error.adhesiveRepulsionFactor"));
        if (attractionFactor < 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Model.NetworkFormationModel.NetworkFormationModel.Error.attractionFactor"));
        if (lambda == 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Model.NetworkFormationModel.NetworkFormationModel.Error.lambda"));
        if (maxAttractionDistance <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Model.NetworkFormationModel.NetworkFormationModel.Error.maxAttractionDistance"));
        if (maxRepulsionDistance <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Model.NetworkFormationModel.NetworkFormationModel.Error.maxRepulsionDistance"));
        if (minAttractionDistance <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Model.NetworkFormationModel.NetworkFormationModel.Error.minAttractionDistance"));
        if (remoteForceFactor < 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Model.NetworkFormationModel.NetworkFormationModel.Error.remoteForceFactor"));
        
        if (minAttractionDistance >= maxAttractionDistance) [[unlikely]] throw ::std::runtime_error(Messages::Get("Model.NetworkFormationModel.NetworkFormationModel.Error.minAttractionDistance-maxAttractionDistance"));
        if (maxRepulsionDistance >= minAttractionDistance) [[unlikely]] throw ::std::runtime_error(Messages::Get("Model.NetworkFormationModel.NetworkFormationModel.Error.maxRepulsionDistance-minAttractionDistance"));
    }

    void NetworkFormationModel::BeforeAdvanceStep(
        const Simulation*,
        SimulationModelStepArgs
    )
    {
    }

    Numerics::Vector3 NetworkFormationModel::ComputeForceOnCell(
        const Simulation*,
        SimulationModelForceComputationArgs args
    ) const
    {
        Numerics::Vector3 force1;
        Numerics::Vector3 force2;
        Numerics::Vector3 force3;

        Cells::CellInfo info{ *args.Target };

        for (const Cells::Cell* pCell : args.Target->AttachedCells()) {
            Numerics::Vector3 diff = info.Position - pCell->Position();
            double dist = diff.Length();

            double v = dist - m_minAttractionDistance;

            if (v > 0.0) {
                force1 -= (v / dist) * diff;
            }
            else {
                v = m_maxRepulsionDistance - dist;

                if (v > 0.0) {
                    force2 += (v / (m_maxRepulsionDistance * dist)) * diff;
                }
            }
        }

        CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE(
            cellInfo,
            args.CellAlgorithm,
            args.Target,
            args.AffectedCells,
            args.Fields,
            {
                if (!cellInfo.IsAlive) continue;

                const Numerics::Vector3 diff = info.Position - cellInfo.Position;
                const double mass            = info.Mass * cellInfo.Mass;

                force3 += (
                    -mass *
                    ::exp(-m_reverseLambda)
                ) * diff;
            }
        )

        return m_attractionFactor * force1 + m_adhesiveRepulsionFactor * force2 + m_remoteForceFactor * force3;
    }

    void NetworkFormationModel::OnAdvanceStep(
        const Simulation* sender,
        SimulationModelStepArgs args
    )
    {
        for (Cells::Cell& cell : *args.Cells) {
            cell.ClearAttachedCells();
        }

// CellListとナイーブの切り替え
#if 1
        m_cellList.ResetCells();
        m_cellList.SetCells(*args.Cells);

        auto begin = args.Cells->begin();
        auto end = args.Cells->end();

        Threading::ThreadPool::ParallelFor(
            begin,
            end,
            [this, args] (Cells::Cell& cell1) {
                if (!cell1.IsAlive()) return;

                CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE(
                    cellInfo,
                    &m_cellList,
                    &cell1,
                    args.Cells,
                    args.Fields,
                    {
                        if (!cellInfo.IsAlive) continue;

                        cell1.Adhere(*cellInfo.CellPtr);
                        //cell2.Adhere(cell1);
                    }
                )

                
            }
        );

        return;
#else
        for (auto itr = args.Cells->begin(), end = args.Cells->end(); itr != end; ++itr) {
            Cells::Cell& cell1 = *itr;

            if (!cell1.IsAlive()) continue;

            for (auto itr2 = itr + 1; itr2 != end; ++itr2) {
                Cells::Cell& cell2 = *itr2;

                if (!cell2.IsAlive()) continue;

                Numerics::Vector3 diff = cell1.Position() - cell2.Position();
                
                if (diff.SquareLength() < m_squareMaxAttractionDistance) {
                    cell1.Adhere(cell2);
                    cell2.Adhere(cell1);
                }
            }
        }
#endif
    }
}