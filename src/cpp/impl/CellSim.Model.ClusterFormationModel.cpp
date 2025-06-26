#include "CellSim.Model.ClusterFormationModel.hpp"
#include "CellSim.Model.SimulationModelForceComputationArgs.hpp"
#include "CellSim.Model.SimulationModelStepArgs.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmAffectableCellQueryArgs.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
#include "CellSim.Settings.Config.SimulationModel.ClusterFormation.hpp"

#include <stdexcept>

namespace CellSim::Model
{
    Numerics::Vector3 ClusterFormationModel::m_computeRemoteForce(
        Cells::CellInfo target,
        Cells::CellInfo cell
    ) const noexcept
    {
        const Numerics::Vector3 diff = target.Position - cell.Position;
        const double mass            = cell.Mass + target.Mass;

        return (
            -mass *
            ::exp(-m_reverseLambda)
        ) * diff;
    }

    Numerics::Vector3 ClusterFormationModel::m_computeVolumeExclusion(
        Cells::CellInfo target,
        Cells::CellInfo cell
    ) const noexcept
    {
        const Numerics::Vector3 diff   = target.Position - cell.Position;
        const double dist = diff.Length();
        const double sumRadius = target.Radius + cell.Radius;

        if (dist < sumRadius) {

            double tmp = 1.0 - dist / sumRadius;

            return diff * (tmp * tmp);
        }

        return Numerics::Vector3();
    }

    ClusterFormationModel::ClusterFormationModel()
        : ClusterFormationModel(
            Settings::Config::SimulationModel::ClusterFormation::AdhesiveRepulsionFactor(),
            Settings::Config::SimulationModel::ClusterFormation::Lambda(),
            Settings::Config::SimulationModel::ClusterFormation::RemoteForceFactor()
        )
    {
    }

    ClusterFormationModel::ClusterFormationModel(
        double adhesiveRepulsionFactor,
        double lambda,
        double remoteForceFactor
    )
        : m_adhesiveRepulsionFactor(adhesiveRepulsionFactor)
        , m_lambda(lambda)
        , m_reverseLambda(1.0 / lambda)
        , m_remoteForceFactor(remoteForceFactor)
    {
        if (adhesiveRepulsionFactor < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Model.ClusterFormationModel.ClusterFormationModel.Error.adhesiveRepulsionFactor"));
        if (lambda == 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Model.ClusterFormationModel.ClusterFormationModel.Error.lambda"));
        if (remoteForceFactor < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Model.ClusterFormationModel.ClusterFormationModel.Error.remoteForceFactor"));
    }

    void ClusterFormationModel::BeforeAdvanceStep(
        const Simulation*,
        SimulationModelStepArgs
    )
    {
    }

    Numerics::Vector3 ClusterFormationModel::ComputeForceOnCell(
        const Simulation*,
        SimulationModelForceComputationArgs args
    ) const
    {
        Cells::CellInfo info{ *args.Target };
        
        if (info.IsAlive) {
            Numerics::Vector3 vec1;
            Numerics::Vector3 vec2;

            CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE(
                cellInfo,
                *args.CellAlgorithm,
                args.Target,
                args.Cells,
                args.Fields,
                {
                    if (cellInfo.IsAlive) {
                        vec1 += m_computeRemoteForce(info, cellInfo);
                    }
                    vec2 += m_computeVolumeExclusion(info, cellInfo);
                }
            )

            return m_remoteForceFactor * vec1 + m_adhesiveRepulsionFactor * vec2;
        }
        
        Numerics::Vector3 vec;

        CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE(
            cellInfo,
            *args.CellAlgorithm,
            args.Target,
            args.Cells,
            args.Fields,
            {
                vec += m_computeVolumeExclusion(info, cellInfo);
            }
        )

        return m_adhesiveRepulsionFactor * vec;
    }

    void ClusterFormationModel::OnAdvanceStep(
        const Simulation*,
        SimulationModelStepArgs
    )
    {
    }
}