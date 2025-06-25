using CellSim.Cells;
using CellSim.Molecular;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.CellAlgorithms
{
    public static class ClusterModel
    {
        public static void Combine(List<Cell> cells, IReadOnlyList<ReadOnlyMoleculeField> fields)
        {
            Combine(cells, fields, null);
        }

        public static void Combine(List<Cell> cells, IReadOnlyList<ReadOnlyMoleculeField> fields, CellList? cellList)
        {
            static void f(Cell cell, CellInfo info, CellInfo cellInfo)
            {
                if (cellInfo.Type == CellType.Invalid) return;
                if (cellInfo.Type != info.Type) return;

                double radius = info.Radius + cellInfo.Radius;

                //距離 < 細胞半径 + 細胞半径 でくっつく
                //高速化のため、２乗で計算
                if ((info.Position - cellInfo.Position).SquareLength < radius * radius)
                {
#pragma warning disable CS8604 // Null 参照引数の可能性があります。
                    cell.Combine(cellInfo.Source as Cell);
#pragma warning restore CS8604 // Null 参照引数の可能性があります。
                }
            }

            if (cellList is null)
            {
                for (int i = 0; i < cells.Count; i++)
                {
                    Cell cell = cells[i];
                    CellInfo info = new CellInfo(cell);
                    for (int j = i + 1; j < cells.Count; j++)
                    {
                        f(cell, info, new CellInfo(cells[j]));
                    }
                }
            }
            else
            {
                foreach (Cell cell in cells)
                {
#pragma warning disable CS8625 // null リテラルを null 非許容参照型に変換できません。
                    CellAlgorithm.Enumerate
                    (
                        null,
                        cellList,
                        cell,
                        cells,
                        fields,
                        cellInfo => f(cell, new CellInfo(cell), cellInfo)
                    );
#pragma warning restore CS8625 // null リテラルを null 非許容参照型に変換できません。
                }
                
            }
        }
    }
}
