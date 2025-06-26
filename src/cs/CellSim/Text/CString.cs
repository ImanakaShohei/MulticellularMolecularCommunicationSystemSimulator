using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace CellSim.Text
{
    public static class CString
    {
        public static string Format(string format, params string[] args)
        {
            string[] s = format.Split("%s");
            StringBuilder stringBuilder = new StringBuilder();
            for (int i = 0; i < s.Length; i++)
            {
                stringBuilder.Append(s[i]);
                if (i != s.Length - 1) stringBuilder.Append($"{{{i}}}");
            }

            return string.Format(stringBuilder.ToString(), args);
        }
    }
}
