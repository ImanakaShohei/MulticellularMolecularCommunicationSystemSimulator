#include "CellSim.Cells.WavePropagationCellBehavior.hpp"
#include "CellSim.Cells.MolecularProcessArgs.hpp"
#include "CellSim.Cells.MolecularProcessResult.hpp"
#include "CellSim.Molecular.MoleculeField.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"

namespace CellSim::Cells
{
    WavePropagationCellBehavior::WavePropagationCellBehavior(
        double cellDivisionRadius,
        double synthesisRate,
        double degradationRate,
        double c,
        double k_1,
        double k_2,
        double l_1,
        double l_2,
        double q,
        double sigma,
        double k_i,
        double k_e,
        double k_t,
        double alpha,
        double h,
        double theta,
        double lambda,
        double epsilon
    )
        : MoleculeAwareCellBehavior(
            cellDivisionRadius,
            synthesisRate,
            degradationRate
        )
        , m_c(c)
        , m_k_1(k_1)
        , m_k_2(k_2)
        , m_l_1(l_1)
        , m_l_2(l_2)
        , m_q(q)
        , m_sigma(sigma)
        , m_k_i(k_i)
        , m_k_e(k_e)
        , m_k_t(k_t)
        , m_alpha(alpha)
        , m_h(h)
        , m_theta(theta)
        , m_lambda(lambda)
        , m_epsilon(epsilon)
    {
    }

    MolecularProcessResult WavePropagationCellBehavior::ComputeMolecularProcess(const Cell* sender, MolecularProcessArgs args)
    {
        MolecularProcessResult result;

        double& rho_T = m_rho_T[args.Kind];

        // dβ/dt
        double diff_beta = ComputeDiffBeta(args.IntracellularAmount, args.ExtracellularAmount, rho_T);
        // dγ/dt
        double diff_gamma = ComputeDiffGamma(args.IntracellularAmount, args.ExtracellularAmount);
        // dρ/dt
        double diff_rho_T = ComputeDiffRhoT(args.ExtracellularAmount, rho_T);

        double deltaTime = Settings::Config::Simulation::DeltaTime();

        rho_T += diff_rho_T * deltaTime;

        result.ExtracellularChange = diff_gamma * deltaTime;
        result.IntracellularChange = diff_beta * deltaTime;
        
        return result;
    }
}