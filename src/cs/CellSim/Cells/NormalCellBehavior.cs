using CellSim.Numerics;
using CellSim.Settings;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cells
{
    public class NormalCellBehavior : CellBehavior
    {
        private static readonly Mutex s_mutex = new Mutex(false);
        private static readonly Random s_random = new Random(Config.Cell.InitialPlacementSeed);
        public override CellBehavior Clone()
        {
            return this;
        }

        public override CellDivisionResult ComputeDivisionOutcome(ReadOnlyCell sender)
        {
            CellDivisionResult result;

            double newRadius = sender.Radius * Math.Cbrt(0.5);
            double newMass = sender.Mass * 0.5;

            Vector3 originalPosition = sender.Position;
            Vector3 direction;

            s_mutex.WaitOne();

            if (Config.Simulation.Enable2DMode)
            {
                double theta = s_random.NextDouble() * Math.PI;
                direction.X = Math.Cos(theta);
                direction.Y = Math.Sin(theta);
                direction.Z = 0;
            }
            else
            {
                double theta = s_random.NextDouble() * (Math.PI * 2.0);
                double phi = Math.Acos(1.0 - 2.0 * s_random.NextDouble());

                double sinPhi = Math.Sin(phi);

                direction.X = sinPhi * Math.Cos(theta);
                direction.Y = sinPhi * Math.Sin(theta);
                direction.Z = Math.Cos(phi);
            }

            s_mutex.ReleaseMutex();

            direction *= newRadius;

            result.NewDaughter.NewMass = newMass;
            result.NewDaughter.NewRadius = newRadius;
            result.NewDaughter.NewPosition = originalPosition + direction;

            result.OriginalDaughter.NewRadius = newRadius;
            result.OriginalDaughter.NewMass = newMass;
            result.OriginalDaughter.NewPosition = originalPosition - direction;

            return result;
        }

        public override CellGrowthResult ComputeGrowth(ReadOnlyCell sender)
        {
            double oldRadius = sender.Radius;
            double newRadius = oldRadius + Config.Cell.GrowthRate * Config.Simulation.DeltaTime;

            double tmp = newRadius / oldRadius;

            double newMass = tmp * tmp * tmp * sender.Mass;

            return new CellGrowthResult(newMass, newRadius);
        }

        public override double ComputeMetabolicChange(ReadOnlyCell sender, CellMetabolicArgs args)
        {
            return 0;
        }

        public override double ComputeMoleculeEmitAmount(ReadOnlyCell sender, CellMoleculeEmissionArgs args)
        {
            return 0;
        }

        public override Vector3 OnSenseMolecules(ReadOnlyCell sender, CellMoleculeSensingArgs args)
        {
            return Vector3.Zero;
        }

        public override bool ShouldDivideThisStep(ReadOnlyCell sender)
        {
            return sender.Radius > Config.CellBehavior.Normal.CellDivisionRadius;
        }
    }
}
