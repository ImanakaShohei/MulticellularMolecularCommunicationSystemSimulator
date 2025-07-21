using CellSim.Molecular;
using CellSim.Numerics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cells
{
    public class ReadOnlyCell
    {
        /// <summary>
        /// ダミー細胞のID
        /// </summary>
        private const uint s_dummyID = unchecked((uint)-1);

        /// <summary>
        /// 各細胞に割り振るID
        /// </summary>
        private static uint s_id = 0;

        /// <summary>
        /// 接着している細胞のリスト
        /// </summary>
        protected readonly List<ReadOnlyCell> m_attachedCells;

        /// <summary>
        /// ふるまい定義
        /// </summary>
        protected CellBehavior m_behavior;

        /// <summary>
        /// 細胞が受けた力
        /// </summary>
        protected Vector3 m_force;

        /// <summary>
        /// 識別子
        /// </summary>
        protected uint m_id;

        /// <summary>
        /// 細胞内の分子の種類とその量
        /// </summary>
        protected readonly List<Molecule> m_internalMolecules;

        /// <summary>
        /// この細胞が生きているかどうか
        /// </summary>
        protected bool m_isAlive;

        /// <summary>
        /// 細胞の質量
        /// </summary>
        protected double m_mass;

        /// <summary>
        /// 極性ベクトル
        /// </summary>
        protected Vector3 m_polarity;

        /// <summary>
        /// 細胞の位置
        /// </summary>
        protected Vector3 m_position;

        /// <summary>
        /// 1step前に細胞が受けた力
        /// </summary>
        protected Vector3 m_previusForce;

        /// <summary>
        /// 細胞の半径
        /// </summary>
        protected double m_radius;

        /// <summary>
        /// 細胞の種類
        /// </summary>
        protected CellType m_type;

#pragma warning disable CS8618 // null 非許容のフィールドには、コンストラクターの終了時に null 以外の値が入っていなければなりません。'required' 修飾子を追加するか、Null 許容として宣言することを検討してください。
        /// <summary>
        /// ダミー用
        /// </summary>
        /// <param name="type"></param>
        /// <param name="mass"></param>
        /// <param name="radius"></param>
        /// <param name="position"></param>
        protected ReadOnlyCell(
            CellType type,
            bool isAlive,
            double mass,
            double radius,
            Vector3 position
        )
#pragma warning restore CS8618 // null 非許容のフィールドには、コンストラクターの終了時に null 以外の値が入っていなければなりません。'required' 修飾子を追加するか、Null 許容として宣言することを検討してください。
        {
            m_id = s_dummyID;
            m_type = type;
            m_isAlive = isAlive;
            m_mass = mass;
            m_radius = radius;
            m_position = position;
        }

        internal ReadOnlyCell(
            CellType type,
            CellBehavior behavior,
            double mass,
            double radius,
            Vector3 position
        )
        {
            m_attachedCells = new List<ReadOnlyCell>();
            m_behavior = behavior;
            m_id = s_id;
            m_internalMolecules = new List<Molecule>();
            m_isAlive = true;
            m_force = new Vector3();
            m_mass = mass;
            m_radius = radius;
            m_position = position;
            m_previusForce = new Vector3();
            m_type = type;

            ArgumentOutOfRangeException.ThrowIfNegativeOrZero(mass, nameof(mass));
            ArgumentOutOfRangeException.ThrowIfNegativeOrZero(radius, nameof(radius));

            ++s_id;
        }

        /// <summary>
        /// 接着している細胞のリスト
        /// </summary>
        public IReadOnlyList<ReadOnlyCell> AttachedCells => m_attachedCells;

        /// <summary>
        /// 接着している細胞の数
        /// </summary>
        public int AttachedCellCount => m_attachedCells.Count;

        /// <summary>
        /// 細胞が受けた力
        /// </summary>
        public Vector3 Force => m_force;

        /// <summary>
        /// 識別子
        /// </summary>
        public uint Id => m_id;

        public IReadOnlyList<ReadOnlyMolecule> InternalMolecules => m_internalMolecules;

        /// <summary>
        /// この細胞が生きているかどうか
        /// </summary>
        public bool IsAlive => m_isAlive;

        /// <summary>
        /// ダミー細胞かどうか
        /// </summary>
        public bool IsDummy => m_id == s_dummyID;

        /// <summary>
        /// 細胞の質量
        /// </summary>
        public double Mass => m_mass;

        /// <summary>
        /// 極性ベクトル
        /// </summary>
        public Vector3 Polarity => m_polarity;

        /// <summary>
        /// 細胞の位置
        /// </summary>
        public Vector3 Position => m_position;

        /// <summary>
        /// 細胞のX座標
        /// </summary>
        public double PositionX => m_position.X;

        /// <summary>
        /// 細胞のY座標
        /// </summary>
        public double PositionY => m_position.Y;

        /// <summary>
        /// 細胞のZ座標
        /// </summary>
        public double PositionZ => m_position.Z;

        /// <summary>
        /// 1step前に細胞が受けた力
        /// </summary>
        public Vector3 PreviusForce => m_previusForce;

        /// <summary>
        /// 1step前の細胞の速度
        /// </summary>
        public Vector3 PreviusVelocity => m_previusForce / m_mass;

        /// <summary>
        /// 細胞の半径
        /// </summary>
        public double Radius => m_radius;

        /// <summary>
        /// このステップで分裂するかどうか
        /// </summary>
        public bool ShouldDivideThisStep => m_behavior.ShouldDivideThisStep(this);

        /// <summary>
        /// 細胞の種類
        /// </summary>
        public CellType Type => m_type;

        /// <summary>
        /// 細胞の速度
        /// </summary>
        public Vector3 Velocity => m_force / m_mass;
    }
}
