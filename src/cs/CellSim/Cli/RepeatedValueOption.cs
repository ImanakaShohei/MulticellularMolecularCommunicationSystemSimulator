using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    /// <summary>
    /// 複数回指定できるオプション
    /// </summary>
    public abstract class RepeatedValueOption : CliOption
    {
        protected readonly List<string> m_values;

        public RepeatedValueOption()
        {
            m_values = new List<string>();
        }

        public override bool HasValue => true;

        public override bool IsRepeatable => true;

        public override string Value => throw new InvalidOperationException();

        public override IReadOnlyList<string> Values => m_values;

        public override void AddValue(string value)
        {
            m_values.Add(value);
        }
    }
}
