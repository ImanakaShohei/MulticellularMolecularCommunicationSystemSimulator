#include "CellSim.Cells.WavePropagationCellBehavior.hpp"
#include "CellSim.Cells.CellMoleculeEmissionArgs.hpp"
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
    
    double WavePropagationCellBehavior::ComputeMoleculeEmitAmount(const Cell*, CellMoleculeEmissionArgs args)
    {
        auto span3 = args.Field->Concentrations();
        double gamma = span3.At(args.Position.X, args.Position.Y, args.Position.Z);

        // dβ/dt
        double diff_beta = ComputeDiffBeta(m_beta, gamma, m_rho_T);
        // dγ/dt
        double diff_gamma = ComputeDiffGamma(m_beta, gamma);
        // dρ/dt
        double diff_rho_T = ComputeDiffRhoT(gamma, m_rho_T);

        double deltaTime = Settings::Config::Simulation::DeltaTime();

        m_beta += diff_beta * deltaTime;
        m_rho_T += diff_rho_T * deltaTime;

        return diff_gamma * deltaTime;
    }
}