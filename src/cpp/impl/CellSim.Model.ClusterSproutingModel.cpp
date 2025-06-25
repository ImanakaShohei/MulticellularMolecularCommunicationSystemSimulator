#include "CellSim.Model.ClusterSproutingModel.hpp"
#include "CellSim.Model.SimulationModelForceComputationArgs.hpp"
#include "CellSim.Model.SimulationModelStepArgs.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmAffectableCellQueryArgs.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Cells.CellBehaviorPtr.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
#include "CellSim.Settings.Config.Cell.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"
#include "CellSim.Settings.Config.SimulationModel.ClusterSprouting.hpp"

#include <numbers>
#include <random>
#include <stdexcept>

namespace CellSim::Model
{
    ClusterSproutingModel::ClusterSproutingModel()
        : ClusterSproutingModel(
            Settings::Config::SimulationModel::ClusterSprouting::AdhesionThreshold(),
            Settings::Config::SimulationModel::ClusterSprouting::CoefficientCd(),
            Settings::Config::SimulationModel::ClusterSprouting::ContactDistance(),
            Settings::Config::SimulationModel::ClusterSprouting::FollowerAttractionFactor(),
            Settings::Config::SimulationModel::ClusterSprouting::GlobalAttractionFactor(),
            Settings::Config::SimulationModel::ClusterSprouting::Lambda(),
            Settings::Config::SimulationModel::ClusterSprouting::LeaderRepulsionFactor(),
            Settings::Config::SimulationModel::ClusterSprouting::LeaderRepulsionMaxDistance(),
            Settings::Config::SimulationModel::ClusterSprouting::LeaderRepulsionMinDistance()
        )
    {
    }

    ClusterSproutingModel::ClusterSproutingModel(
        size_t adhesionThreshold,
        double coefficientCd,
        double contactDistance,
        double followerAttractionFactor,
        double globalAttractionFactor,
        double lambda,
        double leaderRepulsionFactor,
        double leaderRepulsionMaxDistance,
        double leaderRepulsionMinDistance
    )
        : m_adhesionThreshold(adhesionThreshold)
        , m_coefficientCd(coefficientCd)
        , m_contactDistance(contactDistance)
        , m_followerAttractionFactor(followerAttractionFactor)
        , m_globalAttractionFactor(globalAttractionFactor)
        , m_lambda(lambda)
        , m_leaderRepulsionFactor(leaderRepulsionFactor)
        , m_leaderRepulsionMaxDistance(leaderRepulsionMaxDistance)
        , m_leaderRepulsionMinDistance(leaderRepulsionMinDistance)
        , m_leaderRepulsionRange(leaderRepulsionMaxDistance - leaderRepulsionMinDistance)
        , m_squareContactDistance(contactDistance * contactDistance)
    {
        if (coefficientCd < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'coefficientCd' must be greater than or equal to zero.");
        if (contactDistance < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'contactDistance' must be greater than or equal to zero.");
        if (followerAttractionFactor < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'followerAttractionFactor' must be greater than or equal to zero.");
        if (globalAttractionFactor < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'globalAttractionFactor' must be greater than or equal to zero.");
        if (lambda == 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'lambda' must be non-zero.");
        if (leaderRepulsionFactor < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'leaderRepulsionFactor' must be greater than or equal to zero.");
        if (leaderRepulsionMaxDistance < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'leaderRepulsionMaxDistance' must be greater than or equal to zero.");
        if (leaderRepulsionMinDistance < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'leaderRepulsionMinDistance' must be greater than or equal to zero.");
        
        if (m_leaderRepulsionRange <= 0.0) [[unlikely]] throw ::std::invalid_argument("'leaderRepulsionMinDistance' must be less than 'leaderRepulsionMaxDistance'.");
        if (contactDistance >= leaderRepulsionMinDistance) [[unlikely]] throw ::std::invalid_argument("'contactDistance' must be less than 'leaderRepulsionMinDistance'.");
    }

    void ClusterSproutingModel::BeforeAdvanceStep(
        const Simulation*,
        SimulationModelStepArgs args
    )
    {
        for (Cells::Cell& cell : *args.Cells) {
            cell.ClearAttachedCells();
        }

        for (auto itr = args.Cells->begin(), end = args.Cells->end(); itr != end; ++itr) {
            Cells::Cell& cell1 = *itr;

            if (!cell1.IsAlive()) continue;

            for (auto itr2 = itr + 1; itr2 != end; ++itr2) {
                Cells::Cell& cell2 = *itr2;

                if (!cell2.IsAlive()) continue;

                Numerics::Vector3 diff = cell1.Position() - cell2.Position();
                
                if (diff.SquareLength() < m_squareContactDistance) {
                    cell1.Adhere(cell2);
                    cell2.Adhere(cell1);
                }
            }
        }
    }

    Numerics::Vector3 ClusterSproutingModel::ComputeForceOnCell(
        const Simulation*,
        SimulationModelForceComputationArgs args
    ) const
    {
        Numerics::Vector3 force1;
        Numerics::Vector3 force2;
        Numerics::Vector3 force3;
        Numerics::Vector3 force4;
        Cells::CellInfo info{ *args.Target };

        size_t attachedCellCount = args.Target->AttachedCellCount();

        for (const Cells::Cell* pCell : args.Target->AttachedCells()) {
            Numerics::Vector3 diff = info.Position - pCell->Position();
            double dist = diff.Length();

            if (attachedCellCount <= m_adhesionThreshold) {
                // 接着している細胞から離れようとする
                force1 += diff * ((m_leaderRepulsionMaxDistance - dist) / (m_leaderRepulsionMaxDistance * dist));
            }
            else {
                double v = dist - m_leaderRepulsionMinDistance;

                // 近すぎると何も起こらない
                if (v > 0.0) {
                    force2 -= diff * (v / (dist * m_leaderRepulsionRange));
                }
            }

            // 近すぎると反発力が発生
            if (dist < m_contactDistance) {
                force3 += diff * ((m_contactDistance - dist) / (m_contactDistance * dist));
            }
        }

        CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE(
            cellInfo,
            *args.CellAlgorithm,
            args.Target,
            args.Cells,
            args.Fields,
            {
                Numerics::Vector3 diff = info.Position - cellInfo.Position;
                double dist = diff.Length();

                // すべての細胞に働く力
                force4 -= diff * (::exp(-dist / m_lambda) / dist);
            }
        )

        return m_leaderRepulsionFactor * force1 + m_followerAttractionFactor * force2 + m_coefficientCd * force3 + m_globalAttractionFactor * force4;
    }

    void ClusterSproutingModel::OnAdvanceStep(
        const Simulation*,
        SimulationModelStepArgs
    )
    {
    }
}