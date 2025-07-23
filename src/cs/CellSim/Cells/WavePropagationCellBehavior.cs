using CellSim.Molecular;
using CellSim.Settings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cells
{
    public class WavePropagationCellBehavior : MoleculeAwareCellBehavior
    {
        private double m_c;
        private double m_k_1;
        private double m_k_2;
        private double m_l_1;
        private double m_l_2;
        private double m_q;
        private double m_sigma;
        private double m_k_i;
        private double m_k_e;
        private double m_k_t;
        private double m_alpha;
        private double m_h;
        private double m_theta;
        private double m_lambda;
        private double m_epsilon;

        private readonly Dictionary<MoleculeKind, double> m_rho_T;

        private double ComputeDiffBeta(double beta, double gamma, double rho_T)
        {
            return m_q * m_sigma * Phi(gamma, rho_T) - (m_k_i + m_k_t) * beta;
        }

        private double ComputeDiffGamma(double beta, double gamma)
        {
            return (m_k_t * beta) / m_h - m_k_e * gamma;
        }

        private double ComputeDiffRhoT(double gamma, double rho_T)
        {
            return -F1(gamma) * rho_T + F2(gamma) * (1 - rho_T);
        }

        private double F1(double gamma)
        {
            return (m_k_1 + m_k_2 * gamma) / (1 + gamma);
        }

        private double F2(double gamma)
        {
            return (m_k_1 * m_l_1 + m_k_2 * m_l_2 * m_c * gamma) / (1 + m_c * gamma);
        }

        private double Phi(double gamma, double rho_T)
        {
            double y = Y(rho_T, gamma);
            return (m_alpha * (m_lambda * m_theta + m_epsilon * y * y)) / (1 + m_alpha * m_theta + m_epsilon * y * y * (1 + m_alpha));
        }

        private double Y(double gamma, double rho_T)
        {
            return (rho_T * gamma) / (1 + gamma);
        }

        public WavePropagationCellBehavior()
            : this(
                  Config.CellBehavior.WavePropagation.CellDivisionRadius,
                  Config.CellBehavior.WavePropagation.SynthesisRate,
                  Config.CellBehavior.WavePropagation.DegradationRate,
                  Config.CellBehavior.WavePropagation.C,
                  Config.CellBehavior.WavePropagation.K1,
                  Config.CellBehavior.WavePropagation.K2,
                  Config.CellBehavior.WavePropagation.L1,
                  Config.CellBehavior.WavePropagation.L2,
                  Config.CellBehavior.WavePropagation.Q,
                  Config.CellBehavior.WavePropagation.Sigma,
                  Config.CellBehavior.WavePropagation.Ki,
                  Config.CellBehavior.WavePropagation.Ke,
                  Config.CellBehavior.WavePropagation.Kt,
                  Config.CellBehavior.WavePropagation.Alpha,
                  Config.CellBehavior.WavePropagation.H,
                  Config.CellBehavior.WavePropagation.Theta,
                  Config.CellBehavior.WavePropagation.Lambda,
                  Config.CellBehavior.WavePropagation.Epsilon
            )
        {
        }

        public WavePropagationCellBehavior(
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
        ) : base(cellDivisionRadius, synthesisRate, degradationRate)
        {
            m_c = c;
            m_k_1 = k_1;
            m_k_2 = k_2;
            m_l_1 = l_1;
            m_l_2 = l_2;
            m_q = q;
            m_sigma = sigma;
            m_k_i = k_i;
            m_k_e = k_e;
            m_k_t = k_t;
            m_alpha = alpha;
            m_h = h;
            m_theta = theta;
            m_lambda = lambda;
            m_epsilon = epsilon;

            m_rho_T = new Dictionary<MoleculeKind, double>();
        }

        public override CellBehavior Clone()
        {
            return (WavePropagationCellBehavior)MemberwiseClone();
        }

        public override MolecularProcessResult ComputeMolecularProcess(ReadOnlyCell sender, MolecularProcessArgs args)
        {
            MolecularProcessResult result;

            double rho_T = m_rho_T[args.Kind];

            // dβ/dt
            double diff_beta = ComputeDiffBeta(args.IntracellularAmount, args.ExtracellularAmount, rho_T);
            // dγ/dt
            double diff_gamma = ComputeDiffGamma(args.IntracellularAmount, args.ExtracellularAmount);
            // dρ/dt
            double diff_rho_T = ComputeDiffRhoT(args.ExtracellularAmount, rho_T);

            double deltaTime = Config.Simulation.DeltaTime;

            m_rho_T[args.Kind] += diff_rho_T * deltaTime;

            result.ExtracellularChange = diff_gamma * deltaTime;
            result.IntracellularChange = diff_beta * deltaTime;

            return result;
        }
    }
}
