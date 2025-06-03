#include "CellSim.Model.ClusterFormationModel.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
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
        const double mass            = cell.Mass * target.Mass;

        return (
            -mass *
            m_remoteForceFactor *
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
            tmp = m_adhesiveRepulsionFactor * (tmp * tmp);

            return diff * tmp;
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
        if (adhesiveRepulsionFactor < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'adhesiveRepulsionFactor' must be greater than or equal to zero.");
        if (lambda == 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'lambda' must be non-zero.");
        if (remoteForceFactor < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'remoteForceFactor' must be greater than or equal to zero.");
    }

    void ClusterFormationModel::BeforeAdvanceStep(
        ::std::vector<Cells::Cell>&,
        ::std::vector<Molecule::MoleculeDiffusion> const&
    )
    {
    }

    Numerics::Vector3 ClusterFormationModel::ComputeForceOnCell(
        Cells::Cell const& target,
        ::std::vector<Cells::Cell> const& cells,
        ::std::vector<Molecule::MoleculeDiffusion> const& molecules,
        const CellAlgorithms::CellAlgorithm* pCellAlgorithm
    ) const
    {
        Cells::CellInfo info{ target };

        if (info.IsAlive) {
            Numerics::Vector3 vec1;
            Numerics::Vector3 vec2;
            CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE(
                cellInfo,
                *pCellAlgorithm,
                target,
                cells,
                molecules,
                {
                    if (cellInfo.IsAlive) {
                        vec1 += m_computeRemoteForce(info, cellInfo);
                    }
                    vec2 += m_computeVolumeExclusion(info, cellInfo);
                }
            )

            return vec1.Normalize() + vec2;
        }
        
        Numerics::Vector3 vec;

        CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE(
            cellInfo,
            *pCellAlgorithm,
            target,
            cells,
            molecules,
            {
                vec += m_computeVolumeExclusion(info, cellInfo);
            }
        )

        return vec;
    }

    void ClusterFormationModel::OnAdvanceStep(
        ::std::vector<Cells::Cell>&,
        ::std::vector<Molecule::MoleculeDiffusion> const&
    )
    {
    }
}