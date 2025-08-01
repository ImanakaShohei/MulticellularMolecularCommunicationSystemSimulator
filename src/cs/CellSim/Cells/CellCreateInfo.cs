using CellSim.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cells
{
    public struct CellCreateInfo
    {
        /// <summary>
        /// 細胞の成長速度
        /// </summary>
        public double GrowthRate;

        /// <summary>
        /// 細胞の初期質量
        /// </summary>
        public double Mass;

        /// <summary>
        /// 細胞の初期半径
        /// </summary>
        public double Radius;

        /// <summary>
        /// 細胞の初期数
        /// </summary>
        public int CellCount;

        /// <summary>
        /// ふるまい定義
        /// </summary>
        public CellBehaviorType BehaviorType;

        /// <summary>
        /// 細胞の種類
        /// </summary>
        public CellType Type;

        /// <summary>
        /// 画像出力時の色
        /// </summary>
        public Color Color;
    }
}
