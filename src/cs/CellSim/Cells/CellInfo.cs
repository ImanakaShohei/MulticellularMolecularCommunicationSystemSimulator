using CellSim.Numerics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cells
{
    /// <summary>
    /// 細胞の情報
    /// </summary>
    public struct CellInfo
    {
        public ReadOnlyCell? Source;

        public bool IsAlive;
        public double Mass;
        public Vector3 Position;
        public Vector3 PreviusForce;
        public double Radius;
        public CellType Type;

        public CellInfo(ReadOnlyCell cell)
        {
            IsAlive = cell.IsAlive;
            Mass = cell.Mass;
            Position = cell.Position;
            PreviusForce = cell.PreviusForce;
            Radius = cell.Radius;
            Type = cell.Type;

            Source = cell;
        }
        
        public CellInfo(
            double mass,
            bool isAlive,
            Vector3 position,
            Vector3 previusForce,
            double radius,
            CellType type
        )
        {
            IsAlive = isAlive;
            Mass = mass;
            Position = position;
            PreviusForce = previusForce;
            Radius = radius;
            Type = type;

            Source = null;
        }
    }
}
