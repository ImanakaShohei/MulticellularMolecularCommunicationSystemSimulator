using CellSim.Cells;
using CellSim.Model;
using CellSim.Numerics;
using CellSim.Settings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.CellAlgorithms
{
    public class CellList : CellAlgorithm
    {
        private readonly List<CellInfo>[,,] m_cellField;

        private readonly bool m_enable2DMode;

        private readonly int m_gridCountX;
        private readonly int m_gridCountY;
        private readonly int m_gridCountZ;

        private readonly double m_gridLengthX;
        private readonly double m_gridLengthY;
        private readonly double m_gridLengthZ;

        private readonly double m_reverseGridLengthX;
        private readonly double m_reverseGridLengthY;
        private readonly double m_reverseGridLengthZ;

        private readonly int m_searchGridCountX;
        private readonly int m_searchGridCountY;
        private readonly int m_searchGridCountZ;
        private readonly double m_searchRadius;

        private readonly double m_squareSeachRadius;

        public CellList()
            : this(
                Config.CellAlgorithm.CellList.GridCount,
                Config.Simulation.Enable2DMode,
                Config.CellAlgorithm.CellList.SearchRadius
            )
        {
        }

        public CellList(
            int gridCount,
            bool enable2DMode,
            double searchRadius
        )
        {
            if (gridCount == 0) throw new ArgumentOutOfRangeException(Messages.Get("CellAlgorithms.CellList.CellList.Error.gridCount"));
            if (searchRadius < 0.0) throw new ArgumentOutOfRangeException(Messages.Get("CellAlgorithms.CellList.CellList.Error.searchRadius"));

            m_cellField = enable2DMode ? new List<CellInfo>[gridCount, gridCount, 1] : new List<CellInfo>[gridCount, gridCount, gridCount];
            
            for (int i = 0; i < m_cellField.GetLength(0); i++)
            {
                for (int j = 0; j < m_cellField.GetLength(1); j++)
                {
                    for (int k = 0; k < m_cellField.GetLength(2); k++)
                    {
                        m_cellField[i, j, k] = new List<CellInfo>();
                    }
                }
            }

            m_enable2DMode = enable2DMode;
            
            m_gridCountX = gridCount;
            m_gridCountY = gridCount;
            m_gridCountZ = enable2DMode ? 1 : gridCount;

            m_gridLengthX = Config.Simulation.FieldRadiusX * 2.0 / gridCount;
            m_gridLengthY = Config.Simulation.FieldRadiusY * 2.0 / gridCount;
            m_gridLengthZ = Config.Simulation.FieldRadiusZ * 2.0 / m_gridCountZ;

            m_reverseGridLengthX = 1.0 / m_gridLengthX;
            m_reverseGridLengthY = 1.0 / m_gridLengthY;
            m_reverseGridLengthZ = enable2DMode ? 0.0 : 1.0 / m_gridLengthZ;

            m_searchGridCountX = (int)(2.0 * searchRadius / m_gridLengthX);
            m_searchGridCountY = (int)(2.0 * searchRadius / m_gridLengthY);
            m_searchGridCountZ = enable2DMode ? 0 : (int)(2.0 * searchRadius / m_gridLengthZ);

            m_searchRadius = searchRadius;
            m_squareSeachRadius = searchRadius * searchRadius;
        }

        public override bool HasMultithreadingSupport => true;

        public override void BeforeAdvanceStep(ReadOnlySimulation sender, CellAlgorithmStepArgs args)
        {
            SetCells(args.Cells);
        }

        public override IEnumerable<CellInfo> EnumerateAffectableCellInfos(CellSimulationModel sender, CellAlgorithmAffectableCellQueryArgs args)
        {
            Vector3 position = args.Target.Position;
            GridPosition3 gridPosition = ToGridPosition3(position);

            int xMin = gridPosition.X - m_searchGridCountX;
            int yMin = gridPosition.Y - m_searchGridCountY;
            int zMin = gridPosition.Z - m_searchGridCountZ;
            int xMax = gridPosition.X + m_searchGridCountX;
            int yMax = gridPosition.Y + m_searchGridCountY;
            int zMax = gridPosition.Z + m_searchGridCountZ;

            if (xMin < 0) xMin = 0;
            if (yMin < 0) yMin = 0;
            if (zMin < 0) zMin = 0;

            if (xMax >= m_gridCountX) xMax = m_gridCountX - 1;
            if (yMax >= m_gridCountY) yMax = m_gridCountY - 1;
            if (zMax >= m_gridCountZ) zMax = m_gridCountZ - 1;

            for (int x = xMin; x <= xMax; x++)
            {
                for (int y = yMin; y <= yMax; y++)
                {
                    for (int z = zMin; z <= zMax; z++)
                    {
                        foreach (CellInfo info in m_cellField[x, y, z])
                        {
                            if (info.Position == position) continue;

                            if (IsWithinSearchRadius(position, info.Position))
                            {
                                yield return info;
                            }
                        }
                    }
                }
            }
        }

        public override List<CellInfo> GetAffectableCellInfos(CellSimulationModel sender, CellAlgorithmAffectableCellQueryArgs args)
        {
            List<CellInfo> result = new List<CellInfo>();
            Vector3 position = args.Target.Position;
            GridPosition3 gridPosition = ToGridPosition3(position);

            int xMin = gridPosition.X - m_searchGridCountX;
            int yMin = gridPosition.Y - m_searchGridCountY;
            int zMin = gridPosition.Z - m_searchGridCountZ;
            int xMax = gridPosition.X + m_searchGridCountX;
            int yMax = gridPosition.Y + m_searchGridCountY;
            int zMax = gridPosition.Z + m_searchGridCountZ;

            if (xMin < 0) xMin = 0;
            if (yMin < 0) yMin = 0;
            if (zMin < 0) zMin = 0;

            if (xMax >= m_gridCountX) xMax = m_gridCountX - 1;
            if (yMax >= m_gridCountY) yMax = m_gridCountY - 1;
            if (zMax >= m_gridCountZ) zMax = m_gridCountZ - 1;

            for (int x = xMin; x <= xMax; x++)
            {
                for (int y = yMin; y <= yMax; y++)
                {
                    for (int z = zMin; z <= zMax; z++)
                    {
                        foreach (CellInfo info in m_cellField[x, y, z])
                        {
                            if (info.Position == position) continue;

                            if (IsWithinSearchRadius(position, info.Position))
                            {
                                result.Add(info);
                            }
                        }
                    }
                }
            }

            return result;
        }

        public bool IsWithinSearchRadius(Vector3 position1, Vector3 position2) => (position1 - position2).SquareLength < m_squareSeachRadius;
        public bool IsWithinSearchRadius(Vector3 position1, ReadOnlyCell cell2) => IsWithinSearchRadius(position1, cell2.Position);
        public bool IsWithinSearchRadius(ReadOnlyCell cell1, Vector3 position2) => IsWithinSearchRadius(cell1.Position, position2);
        public bool IsWithinSearchRadius(ReadOnlyCell cell1, ReadOnlyCell cell2) => IsWithinSearchRadius(cell1.Position, cell2.Position);

        public override void OnAdvanceStep(ReadOnlySimulation sender, CellAlgorithmStepArgs args)
        {
            ResetCells();
        }

        public void ResetCells()
        {
            foreach (List<CellInfo> list in m_cellField)
            {
                list.Clear();
            }
        }

        public void SetCells(IReadOnlyCollection<ReadOnlyCell> cells)
        {
            foreach (ReadOnlyCell cell in cells)
            {
                Vector3 position = cell.Position;

                double x = position.X + Config.Simulation.FieldRadiusX;

                if (x < 0.0) continue;

                double y = position.Y + Config.Simulation.FieldRadiusY;

                if (y < 0.0) continue;

                double z;

                if (m_enable2DMode)
                {
                    z = 0;
                }
                else
                {
                    z = position.Z + Config.Simulation.FieldRadius;

                    if (z < 0.0) continue;
                }

                int atX = (int)(x * m_reverseGridLengthX);
                int atY = (int)(y * m_reverseGridLengthY);
                int atZ = (int)(z * m_reverseGridLengthZ);

                if (atX >= m_gridCountX) continue;
                if (atY >= m_gridCountY) continue;
                if (atZ >= m_gridCountZ) continue;

                m_cellField[atX, atY, atZ].Add(new CellInfo(cell));
            }
        }

        public GridPosition3 ToGridPosition3(Vector3 position)
        {
            double x = position.X + Config.Simulation.FieldRadius;

            double y = position.Y + Config.Simulation.FieldRadius;

            if (m_enable2DMode)
            {
                return new GridPosition3(
                    (int)(x * m_reverseGridLengthX),
                    (int)(y * m_reverseGridLengthY),
                    0
                );
            }
            else
            {
                double z = position.Z + Config.Simulation.FieldRadius;

                return new GridPosition3(
                    (int)(x * m_reverseGridLengthX),
                    (int)(y * m_reverseGridLengthY),
                    (int)(z * m_reverseGridLengthZ)
                );
            }
        }

        public GridPosition3 ToGridPosition3(ReadOnlyCell cell) => ToGridPosition3(cell.Position);
    }
}
