using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    /// <summary>
    /// 値を持たないオプション
    /// </summary>
    public abstract class FlagOption : CliOption
    {
        public override bool HasValue => false;

        public override bool IsRepeatable => false;

        public override string Value => throw new InvalidOperationException();

        public override IReadOnlyList<string> Values => throw new InvalidOperationException();

        public override void AddValue(string value)
        {
            throw new InvalidOperationException();
        }
    }
}
