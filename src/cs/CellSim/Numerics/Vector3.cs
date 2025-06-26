using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Numerics
{
    public struct Vector3
    {
        public double X;
        public double Y;
        public double Z;

        public static Vector3 Zero => new Vector3(0, 0, 0);

        public Vector3(double x, double y, double z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public readonly double Length => Math.Sqrt(SquareLength);

        public readonly Vector3 Normalized
        {
            get
            {
                double length = Length;
                if (length == 0) return new Vector3();

                return this / length;
            }
        }


        public readonly double SquareLength => X * X + Y * Y + Z * Z;

        public override readonly bool Equals(object? obj)
        {
            if (obj is Vector3 vector) return Equals(vector);
            return false;
        }

        public readonly bool Equals(Vector3 other) => other.X == X && other.Y == Y && other.Z == Z;

        public override readonly int GetHashCode()
        {
            long result = X.GetHashCode();
            result += Y.GetHashCode();
            result += Z.GetHashCode();

            return (int)result;
        }

        public override readonly string ToString() => $"{X},{Y},{Z}";

        public static bool operator ==(Vector3 left, Vector3 right) => left.Equals(right);
        public static bool operator !=(Vector3 left, Vector3 right) => !left.Equals(right);

        public static Vector3 operator +(Vector3 left, Vector3 right) => new Vector3(left.X + right.X, left.Y + right.Y, left.Z + right.Z);
        public static Vector3 operator -(Vector3 left, Vector3 right) => new Vector3(left.X - right.X, left.Y - right.Y, left.Z - right.Z);
        public static Vector3 operator *(Vector3 left, Vector3 right) => new Vector3(left.X * right.X, left.Y * right.Y, left.Z * right.Z);
        public static Vector3 operator *(Vector3 left, double right) => new Vector3(left.X * right, left.Y * right, left.Z * right);

        public static Vector3 operator *(double left, Vector3 right) => new Vector3(left * right.X, left * right.Y, left * right.Z);

        public static Vector3 operator /(Vector3 left, double right) => new Vector3(left.X / right, left.Y / right, left.Z / right);
    }
}
