using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    /// <summary>
    /// 値を持つオプション
    /// </summary>
    public abstract class ValueOption : CliOption
    {
        protected string m_value;

        public ValueOption()
        {
            m_value = "";
        }

        public ValueOption(string value)
        {
            m_value = value;
        }

        public override bool HasValue => true;

        public override bool IsRepeatable => false;

        public override string Value => m_value;

        public override IReadOnlyList<string> Values => throw new InvalidOperationException();

        public override void AddValue(string value)
        {
            m_value = value;
        }
    }
}
