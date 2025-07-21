using CellSim.Molecular;
using CellSim.Numerics;
using CellSim.Settings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cells
{
    /// <summary>
    /// 細胞クラス
    /// </summary>
    public sealed class Cell : ReadOnlyCell
    {
        /// <summary>
        /// ダミー用
        /// </summary>
        /// <param name="type"></param>
        /// <param name="isAlive"></param>
        /// <param name="mass"></param>
        /// <param name="radius"></param>
        /// <param name="position"></param>
        private Cell(
            CellType type,
            bool isAlive,
            double mass,
            double radius,
            Vector3 position
        ) : base(
                type,
                isAlive,
                mass,
                radius,
                position
            )
        {
        }

        public static Cell CreateDummy(
            CellType type,
            bool isAlive,
            double mass,
            double radius,
            Vector3 position
        )
        {
            return new Cell(
                type,
                isAlive,
                mass,
                radius,
                position
            );
        }

        public Cell(
            CellType type,
            CellBehavior behavior,
            double mass,
            double radius,
            Vector3 position
        )
            : base(
                  type,
                  behavior,
                  mass,
                  radius,
                  position
              )
        {
        }

        /// <summary>
        /// 分子を追加
        /// </summary>
        /// <param name="kind">分子の種類</param>
        /// <returns>分子を追加したかどうか</returns>
        /// <remarks>初期状態では分子の数はゼロ</remarks>
        public bool AppendMolecule(MoleculeKind kind)
        {
            foreach (Molecule molecule in m_internalMolecules)
            {
                if (molecule.Kind == kind) return false;
            }

            m_internalMolecules.Add(new Molecule(kind));

            return true;
        }

        /// <summary>
        /// 分子を追加
        /// </summary>
        /// <param name="kind">分子の種類</param>
        /// /// <remarks>初期状態では分子の数はゼロ</remarks>
        public void AppendMoleculeUnsafe(MoleculeKind kind)
        {
            m_internalMolecules.Add(new Molecule(kind));
        }

        /// <summary>
        /// 細胞に力を加える
        /// </summary>
        /// <param name="force">加える力</param>
        public void ApplyForce(Vector3 force)
        {
            m_force += force;
        }

        /// <summary>
        /// 接着
        /// </summary>
        /// <param name="cell">接着する細胞</param>
        public void Adhere(ReadOnlyCell cell)
        {
            m_attachedCells.Add(cell);
        }

        /// <summary>
        /// すべての細胞の接着を解除
        /// </summary>
        public void ClearAttachedCells()
        {
            m_attachedCells.Clear();
        }

        /// <summary>
        /// 結合
        /// </summary>
        /// <param name="cell">結合する細胞</param>
        /// <remarks>結合すると引数に与えたcは無効になります</remarks>
        public void Combine(Cell cell)
        {
            m_radius = Math.Cbrt(m_radius * m_radius * m_radius + cell.m_radius * cell.m_radius * cell.m_radius);
            m_position = (m_position * m_mass + cell.m_position * cell.m_mass) / (m_mass + cell.m_mass);
            m_mass += cell.m_mass;

            cell.m_type = CellType.Invalid;
        }

        /// <summary>
        /// 細胞死
        /// </summary>
        public void Die()
        {
            m_isAlive = false;
        }

        /// <summary>
        /// 分裂
        /// </summary>
        /// <returns>分裂したもう1つの細胞</returns>
        public Cell Divide()
        {
            CellDivisionResult result = m_behavior.ComputeDivisionOutcome(this);

            m_mass = result.OriginalDaughter.NewMass;
            m_position = result.OriginalDaughter.NewPosition;
            m_radius = result.OriginalDaughter.NewRadius;

            Cell newDaughter = new Cell
            (
                m_type,
                m_behavior.Clone(),
                result.NewDaughter.NewMass,
                result.NewDaughter.NewRadius,
                result.NewDaughter.NewPosition
            );

            foreach (Molecule molecule in m_internalMolecules)
            {
                newDaughter.AppendMoleculeUnsafe(molecule.Kind);
            }

            return newDaughter;
        }

        /// <summary>
        /// 分子空間に分子を放出
        /// </summary>
        /// <param name="field">分子空間</param>
        public void EmitMolecule(MoleculeField field)
        {
            GridPosition3 position3 = field.ToGridPosition3(m_position);

            field.Concentrations[position3.X, position3.Y, position3.Z] += m_behavior.ComputeMoleculeEmitAmount(this, new CellMoleculeEmissionArgs(field));
        }

        /// <summary>
        /// 分子空間に分子を放出
        /// </summary>
        /// <param name="fields">分子空間リスト</param>
        public void EmitMolecule(IReadOnlyCollection<MoleculeField> fields)
        {
            foreach (MoleculeField field in fields)
            {
                EmitMolecule(field);
            }
        }

        /// <summary>
        /// 細胞が成長
        /// </summary>
        public void Grow()
        {
            CellGrowthResult result = m_behavior.ComputeGrowth(this);

            m_radius = result.NewRadius;
            m_mass = result.NewMass;
        }

        public bool IsAdheringTo(ReadOnlyCell cell) => m_attachedCells.Contains(cell);

        /// <summary>
        /// 代謝
        /// </summary>
        public void Metabolize()
        {
            foreach (Molecule molecule in m_internalMolecules)
            {
                molecule.Amount += m_behavior.ComputeMetabolicChange(this, new CellMetabolicArgs(new MoleculeInfo(molecule.Amount, molecule.Kind)));
            }
        }

        /// <summary>
        /// 細胞が移動
        /// </summary>
        public void Move()
        {
            m_position += m_force * (Config.Simulation.DeltaTime / m_mass);
        }

        /// <summary>
        /// 細胞にかかっている力をゼロにする
        /// </summary>
        public void ResetForce()
        {
            m_force = Vector3.Zero;
        }

        public void SenseMolecules(MoleculeField field)
        {
            m_force += m_behavior.OnSenseMolecules(this, new CellMoleculeSensingArgs(field));
        }

        public void SenseMolecules(IReadOnlyCollection<MoleculeField> fields)
        {
            foreach (MoleculeField field in fields)
            {
                SenseMolecules(field);
            }
        }
    }
}
