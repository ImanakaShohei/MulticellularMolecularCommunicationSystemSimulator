#include "CellSim.SimulationResultWriter.hpp"
#include "CellSim.Simulation.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmType.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Model.CellSimulationType.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"

#include <fstream>
#include <stdio.h>
#include <stdexcept>

namespace CellSim
{
    void SimulationResultWriter::m_initialize()
    {
        m_option.InitializeDirectories();

        if(m_option.IsOutputVideo()) {
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

        ofs << "ID,Type,Position.X,Position.Y,Position.Z,Velocity.X,Velocity.Y,Velocity.Z,Radius,Mass,AttachedCellCount," << ::std::endl;

        for (Cells::Cell const& cell : cells) {
            Numerics::Vector3 velocity = cell.Velocity();
            ofs << cell.Id() << ',';
            ofs << (int)cell.Type() << ',';
            ofs << cell.PositionX() << ',';
            ofs << cell.PositionY() << ',';
            ofs << cell.PositionZ() << ',';
            ofs << velocity.X << ',';
            ofs << velocity.Y << ',';
            ofs << velocity.Z << ',';
            ofs << cell.Radius() << ',';
            ofs << cell.Mass() << ',';
            ofs << cell.AttachedCellCount() << ',';

            for (const Cells::Cell* attachedCell : cell.AttachedCells()) {
                ofs << attachedCell->Id() << ',';
            }

            ofs << ::std::endl;
        }

        delete[] filePath;
    }

    ::cv::Mat SimulationResultWriter::m_createImage(
        ::std::vector<Cells::Cell> const& cells,
        ::std::vector<Molecular::MoleculeField> const& fields
    )
    {
        ::cv::Mat image{ m_imageSize, m_imageSize, CV_8UC3, ::cv::Scalar(0, 0, 0) };

        int radius = m_imageSize / 2;

        ::cv::circle(
            image,
            ::cv::Point{ radius, radius },
            radius,
            ::cv::Scalar(255, 255, 255),
            1
        );

        ::cv::line(
            image,
            ::cv::Point{ radius, 0 },
            ::cv::Point{ radius, m_imageSize },
            ::cv::Scalar(255, 255, 255),
            1
        );

        ::cv::line(
            image,
            ::cv::Point{ 0, radius },
            ::cv::Point{ m_imageSize, radius },
            ::cv::Scalar(255, 255, 255),
            1
        );

        for (Cells::Cell const& cell : cells) {
            int pointX = (int)((cell.PositionX() + Settings::Config::Simulation::FieldRadiusX()) * m_scale);
            int pointY = (int)((cell.PositionY() + Settings::Config::Simulation::FieldRadiusY()) * m_scale);

            ::cv::circle(
                image,
                ::cv::Point{ pointX, pointY },
                (int)(cell.Radius() * m_scale),
                ::cv::Scalar(255, 255, 0),
                1
            );

            uint32_t id = cell.Id();

            for (const Cells::Cell* pCell : cell.AttachedCells()) {
                if (pCell->Id() < id) continue;

                ::cv::line(
                    image,
                    ::cv::Point{ pointY, pointX },
                    ::cv::Point{ (int)((pCell->PositionY() + Settings::Config::Simulation::FieldRadius()) * m_scale), (int)((pCell->PositionX() + Settings::Config::Simulation::FieldRadiusX()) * m_scale) },
                    ::cv::Scalar(0, 255, 255),
                    1
                );
            }
        }

        return image;
    }

    void SimulationResultWriter::m_saveImage(::cv::Mat const& image, uint64_t step) const
    {
        size_t filePathLength = m_option.OutputImagePath().size() + m_digits + 4; // ".png"
        size_t filePathCapacity = filePathLength + 1;

        // "%s%020llu.png"
        char optionStr[14];
        
        ::snprintf(optionStr, 14, "%%s%%0%lullu.png", (unsigned long)m_digits);
        
        char* filePath = new char[filePathCapacity];

        ::snprintf(filePath, filePathCapacity, optionStr, m_option.OutputImagePath().c_str(), step);

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
        if (m_videoWriter.isOpened()) {
            m_videoWriter.release();
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

        if (m_option.IsOutputImage()) {
            ::cv::Mat image = m_createImage(simulation.Cells(), simulation.Molecules());
            m_saveImage(image, step);

            if (m_option.IsOutputVideo()) {
                m_videoWriter.write(image);
            }

            return;
        }

        if (m_option.IsOutputVideo()) {
            m_videoWriter.write(m_createImage(simulation.Cells(), simulation.Molecules()));
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