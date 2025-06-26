using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public abstract class ReadOnlyCliOption
    {
        public abstract string FullName { get; }

        public abstract bool HasValue { get; }

        /// <summary>
        /// このオプションを複数回指定できるかどうか
        /// </summary>
        public abstract bool IsRepeatable { get; }

        public abstract string Names { get; }

        /// <summary>
        /// このオプションの種類
        /// </summary>
        public abstract CliOptionType OptionType { get; }

        /// <summary>
        /// 'true'のときはオプション自身が主役となって独自の動作を行う
        /// </summary>
        public abstract bool TakesControl { get; }

        /// <summary>
        /// 値
        /// </summary>
        public abstract string Value { get; }

        public abstract IReadOnlyList<string> Values{ get; }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="optionName"></param>
        /// <returns></returns>
        public abstract bool IsMatch(string optionName);
    }
}
