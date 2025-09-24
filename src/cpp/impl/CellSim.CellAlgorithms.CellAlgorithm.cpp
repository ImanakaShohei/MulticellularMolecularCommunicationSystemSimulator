#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmForceComputationArgs.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmInteractionArgs.hpp"
#include "CellSim.CellAlgorithms.BarnesHut.hpp"
#include "CellSim.CellAlgorithms.CellList.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmType.hpp"
#include "CellSim.CellAlgorithms.NaiveAlgorithm.hpp"
#include "CellSim.CellAlgorithms.NullAlgorithm.hpp"
#include "CellSim.CellAlgorithms.ParticleMesh.hpp"
#include "CellSim.Messages.hpp"
#include "../CellSim.Users.UserCellAlgorithm.hpp"

#include <stdexcept>

namespace CellSim::CellAlgorithms
{
    CellAlgorithm* CellAlgorithm::FromType(
        CellAlgorithmType type
    )
    {
        switch (type) {
            case CellAlgorithmType::BarnesHut:    return new BarnesHut();
            case CellAlgorithmType::CellList:     return new CellList();
            case CellAlgorithmType::Naive:        return new NaiveAlgorithm();
            case CellAlgorithmType::Null:         return new NullAlgorithm();
            case CellAlgorithmType::ParticleMesh: return new ParticleMesh();
            case CellAlgorithmType::User:         return new Users::UserCellAlgorithm();

            default: [[unlikely]]
            {
                throw ::std::invalid_argument(
                    Messages::Get("CellAlgorithms.CellAlgorithm.FromType.Error")
                );
            }
        }
    }

    void CellAlgorithm::ApplyInteraction(
        const Simulation*,
        CellAlgorithmInteractionArgs
    )
    {
    }

    Numerics::Vector3 CellAlgorithm::ComputeForceOnCell(
        const Simulation*,
        CellAlgorithmForceComputationArgs
    ) const
    {
        return Numerics::Vector3();
    }

    bool CellAlgorithm::OverrideForceComputation() const noexcept
    {
        return false;
    }

    bool CellAlgorithm::OverrideInteraction() const noexcept
    {
        return false;
    }
}