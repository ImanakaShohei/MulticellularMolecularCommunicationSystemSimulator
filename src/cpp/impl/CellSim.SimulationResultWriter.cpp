#include "CellSim.SimulationResultWriter.hpp"
#include "CellSim.Simulation.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmType.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Imaging.ImageHelper.hpp"
#include "CellSim.IO.DirectoryCreater.hpp"
#include "CellSim.Model.CellSimulationType.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"

#include <fstream>
#include <optional>
#include <stdio.h>
#include <stdexcept>

namespace CellSim
{
    void SimulationResultWriter::m_initialize()
    {
        m_option.InitializeDirectories();

        if (m_option.IsOutputVideo()) {
            int fourcc = ::cv::VideoWriter::fourcc('M', 'J', 'P', 'G');

            bool v = m_videoWriter.open(
                m_option.OutputPath() + "out.avi",
                fourcc,
                20,
                cv::Size(
                    m_imageSize,
                    m_imageSize
                ),
                true
            );
        }
    }

    void SimulationResultWriter::m_saveBinaryCells(::std::vector<Cells::Cell> const& cells, uint64_t step) const
    {
        size_t filePathLength = m_option.OutputBinaryCellPath().size() + m_digits + 4; // ".bin"
        size_t filePathCapacity = filePathLength + 1;

        // "%s%020llu.bin"
        char optionStr[14];
        
        ::snprintf(optionStr, 14, "%%s%%0%lullu.bin", (unsigned long)m_digits);
        
        char* filePath = new char[filePathCapacity];

        ::snprintf(filePath, filePathCapacity, optionStr, m_option.OutputBinaryCellPath().c_str(), step);

        ::FILE* fp = ::fopen(filePath, "wb");

        if (fp == nullptr) [[unlikely]] throw ::std::runtime_error("Failed to create .bin file");

        for (Cells::Cell const& cell : cells) {
            uint32_t id = cell.Id();
            ::fwrite(&id, sizeof(id), 1, fp);

            Numerics::Vector3 position = cell.Position();
            ::fwrite(&position, sizeof(position), 1, fp);

            Numerics::Vector3 velocity = cell.Velocity();
            ::fwrite(&velocity, sizeof(position), 1, fp);

            double radius = cell.Radius();
            ::fwrite(&radius, sizeof(radius), 1, fp);

            double mass = cell.Mass();
            ::fwrite(&mass, sizeof(mass), 1, fp);

            bool isAlive = cell.IsAlive();
            ::fwrite(&isAlive, sizeof(isAlive), 1, fp);

            uint64_t attachedCellCount = cell.AttachedCellCount();
            ::fwrite(&attachedCellCount, sizeof(attachedCellCount), 1, fp);

            for (const Cells::Cell* attachedCell : cell.AttachedCells()) {
                id = attachedCell->Id();
                ::fwrite(&id, sizeof(id), 1, fp);
            }
        }

        delete[] filePath;
        ::fclose(fp);
    }

    void SimulationResultWriter::m_saveBinaryMolecules([[maybe_unused]] ::std::vector<Molecular::MoleculeField> const& cells, [[maybe_unused]] uint64_t step) const
    {
        // TODO: ここに処理を追加します
    }

    void SimulationResultWriter::m_saveCsvMolecules([[maybe_unused]] ::std::vector<Molecular::MoleculeField> const& cells, [[maybe_unused]] uint64_t step) const
    {
        // TODO: ここに処理を追加します
    }

    void SimulationResultWriter::m_saveCsvCells(::std::vector<Cells::Cell> const& cells, uint64_t step) const
    {
        size_t filePathLength = m_option.OutputCsvCellPath().size() + m_digits + 4; // ".csv"
        size_t filePathCapacity = filePathLength + 1;

        // "%s%020llu.csv"
        char optionStr[14];
        
        ::snprintf(optionStr, 14, "%%s%%0%lullu.csv", (unsigned long)m_digits);
        
        char* filePath = new char[filePathCapacity];

        ::snprintf(filePath, filePathCapacity, optionStr, m_option.OutputCsvCellPath().c_str(), step);

        ::std::ofstream ofs(filePath);
        
        if (!filePath) [[unlikely]] throw ::std::runtime_error("Failed to create .bin file");

        ofs << "ID,Type,Position.X,Position.Y,Position.Z,Velocity.X,Velocity.Y,Velocity.Z,Radius,Mass,IsAlive,AttachedCellCount," << ::std::endl;

        for (Cells::Cell const& cell : cells) {
            Numerics::Vector3 velocity = cell.Velocity();
            ofs << cell.Id() << ',';
            ofs << cell.Type().Name() << ',';
            ofs << cell.PositionX() << ',';
            ofs << cell.PositionY() << ',';
            ofs << cell.PositionZ() << ',';
            ofs << velocity.X << ',';
            ofs << velocity.Y << ',';
            ofs << velocity.Z << ',';
            ofs << cell.Radius() << ',';
            ofs << cell.Mass() << ',';
            ofs << (cell.IsAlive() ? '1' : '0') << ',';
            ofs << cell.AttachedCellCount() << ',';

            for (const Cells::Cell* attachedCell : cell.AttachedCells()) {
                ofs << attachedCell->Id() << ',';
            }

            ofs << ::std::endl;
        }

        delete[] filePath;
    }

    ::cv::Mat SimulationResultWriter::m_createImage(bool isTransparent) const
    {
        return ::cv::Mat{ m_imageSize, m_imageSize, CV_8UC4, isTransparent ? ::cv::Scalar(0, 0, 0, 255) : ::cv::Scalar(0, 0, 0, 255) };
    }

    ::cv::Mat SimulationResultWriter::m_drawCells(::std::vector<Cells::Cell> const& cells) const
    {
        ::cv::Mat image = m_createImage();
        m_drawCells(cells, image);

        return image;
    }

    void SimulationResultWriter::m_drawCells(::std::vector<Cells::Cell> const& cells, ::cv::Mat& image) const
    {
        int radius = m_imageSize / 2;

        ::cv::circle(
            image,
            ::cv::Point{ radius, radius },
            radius,
            ::cv::Scalar(255, 255, 255, 255),
            1
        );

        ::cv::line(
            image,
            ::cv::Point{ radius, 0 },
            ::cv::Point{ radius, m_imageSize },
            ::cv::Scalar(255, 255, 255, 255),
            1
        );

        ::cv::line(
            image,
            ::cv::Point{ 0, radius },
            ::cv::Point{ m_imageSize, radius },
            ::cv::Scalar(255, 255, 255, 255),
            1
        );

        for (Cells::Cell const& cell : cells) {
            int pointX = (int)((cell.PositionX() + Settings::Config::Simulation::FieldRadiusX()) * m_scale);
            int pointY = (int)((cell.PositionY() + Settings::Config::Simulation::FieldRadiusY()) * m_scale);

            Graphics::Color color = cell.Type().Color();

            ::cv::circle(
                image,
                ::cv::Point{ pointX, pointY },
                (int)(cell.Radius() * m_scale),
                ::cv::Scalar(color.B, color.G, color.R),
                1
            );

            uint32_t id = cell.Id();

            for (const Cells::Cell* pCell : cell.AttachedCells()) {
                if (pCell->Id() < id) continue;

                ::cv::line(
                    image,
                    ::cv::Point{ pointY, pointX },
                    ::cv::Point{ (int)((pCell->PositionY() + Settings::Config::Simulation::FieldRadius()) * m_scale), (int)((pCell->PositionX() + Settings::Config::Simulation::FieldRadiusX()) * m_scale) },
                    ::cv::Scalar(0, 255, 255, 255),
                    1
                );
            }
        }
    }

    void SimulationResultWriter::m_drawMolecule(Molecular::MoleculeField const& field, ::cv::Mat& image) const
    {
        ::cv::Scalar color(0, 255, 0, 255);
        double threshold = field.Kind().Threshold();

        size_t z = field.Enable2dMode() ? 0 : field.GridCountZ() / 2;
        int rectLength = (int)(m_imageSize / field.GridCountX());
        
        for (size_t x = 0; x < field.GridCountX(); ++x) {
            auto span2 = field.Concentrations()[x];
            for (size_t y = 0; y < field.GridCountY(); ++y) {
                double value = span2.At(y, z);

                // 透明度設定
                if (value < threshold) {
                    color[3] = (value / threshold) * 255;
                }
                else {
                    color[3] = 255;
                }

                // 位置ずれを最小限に抑えるために毎回位置を計算する
                int pointX = (int)(x * m_imageSize / field.GridCountX());
                int pointY = (int)(y * m_imageSize / field.GridCountY());

                ::cv::rectangle(
                    image,
                    ::cv::Rect{ pointX, pointY, rectLength, rectLength },
                    color,
                    ::cv::LineTypes::FILLED // 塗りつぶし
                );
            }
        }
    }

    void SimulationResultWriter::m_saveImage(::cv::Mat const& image, ::std::string const& parentPath, uint64_t step) const
    {
        size_t filePathLength = parentPath.size() + m_digits + 4; // ".png"
        size_t filePathCapacity = filePathLength + 1;

        // "%s%020llu.png"
        char optionStr[14];
        
        ::snprintf(optionStr, 14, "%%s%%0%lullu.png", (unsigned long)m_digits);
        
        char* filePath = new char[filePathCapacity];

        ::snprintf(filePath, filePathCapacity, optionStr, parentPath.c_str(), step);

        ::cv::imwrite(filePath, image);

        delete[] filePath;
    }

    SimulationResultWriter::SimulationResultWriter(SimulationOption option)
        : m_option(::std::move(option))
        , m_digits(s_log10(Settings::Config::Simulation::TotalSteps()))
        , m_imageSize(Settings::Config::Simulation::ImageSize())
        , m_scale(Settings::Config::Simulation::ImageSize() / 2 / Settings::Config::Simulation::FieldRadius())
        , m_videoWriter()
    {
        m_initialize();
    }

    SimulationResultWriter::~SimulationResultWriter()
    {
        auto f = [](::cv::VideoWriter& writer) {
            if (writer.isOpened()) writer.release();
        };
        
        f(m_videoWriter);

        for (auto& pair : m_moleculeVideos) {
            f(pair.second);
        }
    }

    void SimulationResultWriter::InitializeMoleculeVideos(::std::vector<Molecular::MoleculeField> const& fields)
    {
        for (const Molecular::MoleculeField& field : fields) {
            auto& videoWriter = m_moleculeVideos[field.Kind()];

            if (m_option.IsOutputImage()) {
                IO::DirectoryCreater::Create(m_option.OutputImagePath() + field.Kind().Name());
            }

            if (m_option.IsOutputVideo()) {
                int fourcc = ::cv::VideoWriter::fourcc('M', 'J', 'P', 'G');

                bool v = videoWriter.open(
                    m_option.OutputPath() + "out-" + field.Kind().Name() + ".avi",
                    fourcc,
                    20,
                    cv::Size(
                        m_imageSize,
                        m_imageSize
                    ),
                    true
                );
            }
        }
    }

    void SimulationResultWriter::Save(Simulation const& simulation, uint64_t step)
    {
        if (m_option.IsOutputBinary()) {
            m_saveBinaryCells(simulation.Cells(), step);
            m_saveBinaryMolecules(simulation.Molecules(), step);
        }

        if (m_option.IsOutputCsv()) {
            m_saveCsvCells(simulation.Cells(), step);
            m_saveCsvMolecules(simulation.Molecules(), step);
        }

        if (!m_option.IsOutputImage() && !m_option.IsOutputVideo()) return;

        if (simulation.Molecules().empty()) {
            ::cv::Mat image = m_drawCells(simulation.Cells());
            if (m_option.IsOutputImage()) m_saveImage(image, m_option.OutputImagePath(), step);
        
            if (m_option.IsOutputVideo()) {
                m_videoWriter.write(image);
            }
        }
        else {
            ::cv::Mat image = m_createImage();
            ::cv::Mat cellImage = m_createImage(true);
            m_drawCells(simulation.Cells(), cellImage);

            for (const Molecular::MoleculeField& field : simulation.Molecules()) {
                ::cv::Mat moleculeImage = m_createImage();
                m_drawMolecule(field, moleculeImage);

                // 画像を合成
                ::cv::Mat combinedMolecular = Imaging::ImageHelper::CombineImages(moleculeImage, cellImage);

                if (m_option.IsOutputVideo()) {
                    m_moleculeVideos[field.Kind()].write(combinedMolecular);
                }
            }

            ::cv::Mat combined = Imaging::ImageHelper::CombineImages(image, cellImage);
            if (m_option.IsOutputImage()) m_saveImage(combined, m_option.OutputImagePath(), step);

            if (m_option.IsOutputVideo()) {
                m_videoWriter.write(combined);
            }
        }
        
    }

    void SimulationResultWriter::SaveConfig(
        uint64_t totalStep,
        size_t initialCellCount,
        int64_t totalMilliSeconds,
        Model::CellSimulationType simulationType,
        CellAlgorithms::CellAlgorithmType algorithmType
    )
    {
        ::std::ofstream ofs(m_option.OutputPath() + "config.txt");

        if (!ofs) [[unlikely]] throw ::std::runtime_error("Failed to create config.txt file");

        ofs << "Initial cell count      : " << initialCellCount << ::std::endl;
        ofs << "Total processing time   : " << totalMilliSeconds << " milliseconds" << ::std::endl;
        ofs << "Average processing time : " << ((double)totalMilliSeconds / totalStep) << " milliseconds" << ::std::endl;
        ofs << "Simulation model        : ";

        switch (simulationType) {
            case Model::CellSimulationType::CellGrowth:       ofs << "CellGrowth";       break;
            case Model::CellSimulationType::ClusterFormation: ofs << "ClusterFormation"; break;
            case Model::CellSimulationType::ClusterRotation:  ofs << "ClusterRotation";  break;
            case Model::CellSimulationType::ClusterSprouting: ofs << "ClusterSprouting"; break;
            case Model::CellSimulationType::NetworkFormation: ofs << "NetworkFormation"; break;
            case Model::CellSimulationType::Null:             ofs << "Null";             break;
            case Model::CellSimulationType::User:             ofs << "User";             break;
        }

        ofs << ::std::endl;

        ofs << "Algorithm               : ";

        switch (algorithmType) {
            case CellAlgorithms::CellAlgorithmType::BarnesHut: ofs << "BarnesHut"; break;
            case CellAlgorithms::CellAlgorithmType::CellList: ofs << "CellList"; break;
            case CellAlgorithms::CellAlgorithmType::Naive: ofs << "Naive"; break;
            case CellAlgorithms::CellAlgorithmType::Null: ofs << "Null"; break;
            case CellAlgorithms::CellAlgorithmType::ParticleMesh: ofs << "ParticleMesh"; break;
            case CellAlgorithms::CellAlgorithmType::User: ofs << "User"; break;
        }

        if (Settings::Config::CellAlgorithm::UseClusterModel()) ofs << "+Cluster";
        
        ofs << ::std::endl;
    }
}