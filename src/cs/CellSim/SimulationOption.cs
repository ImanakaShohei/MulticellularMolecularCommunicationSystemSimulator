using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim
{
    /// <summary>
    /// コマンドラインで指定したシミュレーションで使用するオプション
    /// </summary>
    public readonly struct SimulationOption
    {
        /// <summary>
        /// データをバイナリファイルとして出力するかどうか
        /// </summary>
        public readonly bool IsOutputBinary;

        /// <summary>
        /// データをバイナリファイルとして出力するかどうか
        /// </summary>
        public readonly bool IsOutputCsv;

        /// <summary>
        /// データを画像として出力するかどうか
        /// </summary>
        public readonly bool IsOutputImage;

        /// <summary>
        /// データを動画として出力するかどうか
        /// </summary>
        public readonly bool IsOutputVideo;

        public readonly string OutputPath;
        public readonly string OutputBinaryPath;
        public readonly string OutputBinaryCellPath;
        public readonly string OutputBinaryMoleculePath;
        public readonly string OutputCsvPath;
        public readonly string OutputCsvCellPath;
        public readonly string OutputCsvMoleculePath;
        public readonly string OutputImagePath;

        public SimulationOption(
            bool isOutputBinary,
            bool isOutputCsv,
            bool isOutputImage,
            bool isOutputVideo,
            string outputPath
        )
        {
            IsOutputBinary = isOutputBinary;
            IsOutputCsv = isOutputCsv;
            IsOutputImage = isOutputImage;
            IsOutputVideo = isOutputVideo;

            if (!outputPath.EndsWith('\\') && !outputPath.EndsWith('/'))
            {
                OutputPath = $"{outputPath}{Path.DirectorySeparatorChar}";
            }
            else
            {
                OutputPath = outputPath;
            }

            OutputBinaryPath = $"{OutputPath}bin{Path.DirectorySeparatorChar}";
            OutputCsvPath = $"{OutputPath}csv{Path.DirectorySeparatorChar}";
            OutputImagePath = $"{OutputPath}image{Path.DirectorySeparatorChar}";

            OutputBinaryCellPath = $"{OutputBinaryPath}cells{Path.DirectorySeparatorChar}";
            OutputBinaryMoleculePath = $"{OutputBinaryPath}molecules{Path.DirectorySeparatorChar}";
            OutputCsvCellPath = $"{OutputCsvPath}cells{Path.DirectorySeparatorChar}";
            OutputCsvMoleculePath = $"{OutputCsvPath}molecules{Path.DirectorySeparatorChar}";
        }

        public void InitializeDirectories()
        {
            static void f(string p, bool create)
            {
                if (Path.Exists(p))
                {
                    if (Directory.Exists(p))
                    {
                        Directory.Delete(p, true);
                    }
                    else
                    {
                        File.Delete(p);
                    }
                }

                if (create)
                {
                    Directory.CreateDirectory(p);
                }
            }

            f(OutputPath, true);
            f(OutputBinaryPath, IsOutputBinary);
            f(OutputBinaryCellPath, IsOutputBinary);
            f(OutputBinaryMoleculePath, IsOutputBinary);
            f(OutputCsvPath, IsOutputCsv);
            f(OutputCsvCellPath, IsOutputCsv);
            f(OutputCsvMoleculePath, IsOutputCsv);
            f(OutputImagePath, IsOutputImage);
        }
    }
}
