using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Graphics
{
    /// <summary>
    /// ARGBカラー値
    /// </summary>
    public struct Color
    {
        
        public static Color Transparent => new Color(0, 0, 0, 0);

        public byte A;
        public byte R;
        public byte G;
        public byte B;

        public Color()
        {
        }

        public Color(string value)
        {
            A = 255;

            if (value.Length != 7) throw new ArgumentException("Color::Color(::std::string_view): value.size() != 7");
            if (value[0] != '#') throw new ArgumentException("Color::Color(::std::string_view): value[0] != '#'");

            static byte f(string subString)
            {
                Span<byte> values = stackalloc byte[2];

                for (int i = 0; i < 2; i++)
                {
                    char c = subString[i];

                    if ('0' <= c && c <= '9')
                    {
                        values[i] = (byte)(c - '0');
                        continue;
                    }
                    if ('A' <= c && c <= 'F')
                    {
                        values[i] = (byte)(c - 'A' + 10);
                        continue;
                    }
                    if ('a' <= c && c <= 'f')
                    {
                        values[i] = (byte)(c - 'a' + 10);
                        continue;
                    }

                    throw new ArgumentException("Color::Color(::std::string_view): invalid color value.");
                }

                return (byte)(values[0] * 16 + values[1]);
            }

            R = f(value[1..3]);
            G = f(value[3..5]);
            B = f(value[5..7]);
        }

        public Color(byte r, byte g, byte b)
        {
            A = 255;
            R = r;
            G = g; 
            B = b;
        }
        public Color(byte a, byte r, byte g, byte b)
        {
            A = a;
            R = r;
            G = g;
            B = b;
        }

        public override readonly string ToString() => string.Format("#{0:X2}{1:X2}{2:X2}{3:X2}", A, R, G, B);
    }
}
