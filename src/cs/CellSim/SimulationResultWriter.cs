using CellSim.CellAlgorithms;
using CellSim.Cells;
using CellSim.Model;
using CellSim.Molecular;
using CellSim.Numerics;
using CellSim.Settings;
using OpenCvSharp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim
{
    /// <summary>
    /// シミュレーション結果の出力
    /// </summary>
    public sealed class SimulationResultWriter : IDisposable
    {
        private static uint Log10(ulong step)
        {
            if (step == 0) return 1;

            uint result = 0;

            while (step != 0)
            {
                step /= 10;
                ++result;
            }

            return result;
        }

        private readonly SimulationOption m_option;

        /// <summary>
        /// ステップ数の桁数
        /// </summary>
        private readonly uint m_digits;

        private readonly VideoWriter m_videoWriter;

        private void Initialize()
        {
            m_option.InitializeDirectories();

            if (m_option.IsOutputVideo)
            {
                int fourcc = VideoWriter.FourCC("MPEG");

                _ = m_videoWriter.Open(
                    $"{m_option.OutputPath}out.avi",
                    fourcc,
                    20,
                    new Size(
                        Config.Simulation.FieldRadius * 2.0,
                        Config.Simulation.FieldRadius * 2.0
                    ),
                    true
                );
            }
        }

        private void SaveBinaryCells(IReadOnlyList<ReadOnlyCell> cells, ulong step)
        {
            // "{0}{1,0:0000}.bin"
            string optionStr = $"{{0}}{{1,0:{new string('0', (int)m_digits)}}}.bin";

            string filePath = string.Format(optionStr, m_option.OutputBinaryCellPath, step);

            using FileStream fileStream = new FileStream(filePath, FileMode.Create);
            using BinaryWriter writer = new BinaryWriter(fileStream);

            static void writeVector3(BinaryWriter writer, Vector3 vector3)
            {
                writer.Write(vector3.X);
                writer.Write(vector3.Y);
                writer.Write(vector3.Z);
            }

            foreach (ReadOnlyCell cell in cells)
            {
                writer.Write(cell.Id);

                writeVector3(writer, cell.Position);
                writeVector3(writer, cell.Velocity);

                writer.Write(cell.Radius);

                writer.Write(cell.Mass);

                writer.Write((ulong)cell.AttachedCellCount);

                foreach (ReadOnlyCell attachedCell in cell.AttachedCells)
                {
                    writer.Write(attachedCell.Id);
                }
            }
        }

        private void SaveBinaryMolecules(IReadOnlyList<ReadOnlyMoleculeField> fields, ulong step)
        {
            // TODO: ここに処理を追加します
        }

        private void SaveCsvCells(IReadOnlyList<ReadOnlyCell> cells, ulong step)
        {
            // "{0}{1,0:0000}.csv"
            string optionStr = $"{{0}}{{1,0:{new string('0', (int)m_digits)}}}.csv";

            string filePath = string.Format(optionStr, m_option.OutputCsvCellPath, step);

            using StreamWriter writer = new StreamWriter(filePath);

            writer.WriteLine("ID,Type,Position.X,Position.Y,Position.Z,Velocity.X,Velocity.Y,Velocity.Z,Radius,Mass,AttachedCellCount,");

            foreach (ReadOnlyCell cell in cells)
            {
                Vector3 velocity = cell.Velocity;

                writer.Write($"{cell.Id},");
                writer.Write($"{(int)cell.Type},");
                writer.Write($"{cell.PositionX},");
                writer.Write($"{cell.PositionY},");
                writer.Write($"{cell.PositionZ},");
                writer.Write($"{velocity.X},");
                writer.Write($"{velocity.Y},");
                writer.Write($"{velocity.Z},");
                writer.Write($"{cell.Radius},");
                writer.Write($"{cell.Mass},");
                writer.Write($"{cell.AttachedCellCount},");

                foreach (ReadOnlyCell attachedCell in cell.AttachedCells)
                {
                    writer.Write($"{attachedCell.Id},");
                }

                writer.WriteLine();
            }
        }

        private void SaveCsvMolecules(IReadOnlyList<ReadOnlyMoleculeField> fields, ulong step)
        {
            // TODO: ここに処理を追加します
        }

        private static Mat CreateImage(IReadOnlyList<ReadOnlyCell> cells, IReadOnlyList<ReadOnlyMoleculeField> fields)
        {
            int radius = (int)Config.Simulation.FieldRadius;

            int height = (int)(Config.Simulation.FieldRadius * 2.0);
            int width = height;

            Mat image = new Mat(height, width, MatType.CV_8UC3, new Scalar(0, 0, 0));

            Cv2.Circle(
                image,
                new Point(radius, radius),
                radius,
                new Scalar(255, 255, 255),
                1
            );

            Cv2.Line(
                image,
                new Point(radius, 0),
                new Point(radius, height),
                new Scalar(255, 255, 255),
                1
            );

            Cv2.Line(
                image,
                new Point(0, radius),
                new Point(width, radius),
                new Scalar(255, 255, 255),
                1
            );

            foreach (ReadOnlyCell cell in cells)
            {
                int pointX = (int)(cell.PositionX + Config.Simulation.FieldRadiusX);
                int pointY = (int)(cell.PositionY + Config.Simulation.FieldRadiusY);

                Cv2.Circle(
                    image,
                    new Point(pointX, pointY),
                    (int)cell.Radius,
                    new Scalar(255, 255, 0),
                    1
                );

                uint id = cell.Id;

                foreach (ReadOnlyCell attachedCell in cell.AttachedCells)
                {
                    if (attachedCell.Id < id) continue;

                    Cv2.Line(
                        image,
                        new Point(pointX, pointY),
                        new Point(attachedCell.PositionX + Config.Simulation.FieldRadiusX, attachedCell.PositionY + Config.Simulation.FieldRadiusY),
                        new Scalar(255, 255, 0),
                        1
                    );
                }
            }

            return image;
        }

        private void SaveImage(Mat image, ulong step)
        {
            // "{0}{1,0:0000}.png"
            string optionStr = $"{{0}}{{1,0:{new string('0', (int)m_digits)}}}.png";

            string filePath = string.Format(optionStr, m_option.OutputImagePath, step);

            Cv2.ImWrite(filePath, image);
        }

        public SimulationResultWriter(SimulationOption option)
        {
            m_option = option;
            m_digits = Log10(Config.Simulation.TotalSteps);
            m_videoWriter = new VideoWriter();

            Initialize();
        }

        public void Dispose()
        {
            if (m_videoWriter.IsOpened())
            {
                m_videoWriter.Release();
                GC.SuppressFinalize(this);
            }
        }

        public void Save(ReadOnlySimulation simulation, ulong step)
        {
            if (m_option.IsOutputBinary)
            {
                SaveBinaryCells(simulation.Cells, step);
                SaveBinaryMolecules(simulation.Molecules, step);
            }

            if (m_option.IsOutputCsv)
            {
                SaveCsvCells(simulation.Cells, step);
                SaveCsvMolecules(simulation.Molecules, step);
            }

            if (m_option.IsOutputImage)
            {
                Mat image = CreateImage(simulation.Cells, simulation.Molecules);
                SaveImage(image, step);

                if (m_option.IsOutputVideo)
                {
                    m_videoWriter.Write(image);
                }

                return;
            }

            if (m_option.IsOutputVideo)
            {
                m_videoWriter.Write(CreateImage(simulation.Cells, simulation.Molecules));
            }
        }

        public void SaveConfig(
            ulong totalStep,
            int initialCellCount,
            long totalMilliSeconds,
            CellSimulationType simulationType,
            CellAlgorithmType algorithmType
        )
        {
            using StreamWriter writer = new StreamWriter($"{m_option.OutputPath}config.txt");

            writer.WriteLine($"Initial cell count      : {initialCellCount}");
            writer.WriteLine($"Total processing time   : {totalMilliSeconds} milliseconds");
            writer.WriteLine($"Average processing time : {(double)totalMilliSeconds / totalStep} milliseconds");
            writer.WriteLine($"Simulation model        : {simulationType}");
            writer.Write($"Algorithm               : {algorithmType}");

            if (Config.CellAlgorithm.UseClusterModel) writer.Write("+Cluster");

            writer.WriteLine();
        }
    }
}
