#include "Cellsim.SimulationResultWriter.hpp"
#include "CellSim.Simulation.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"

#include <fstream>
#include <stdio.h>
#include <stdexcept>

namespace CellSim
{
    void SimulationResultWriter::m_saveBinaryCells(::std::vector<Cells::Cell> const& cells, uint64_t step) const
    {
        size_t filePathLength = m_option.OutputBinaryCellPath().size() + m_digits + 4; // ".bin"
        size_t filePathCapacity = filePathLength + 1;

        // "%s%020llu.bin"
        char optionStr[14];
        
        ::snprintf(optionStr, 14, "%%s0%%%lu.bin", m_digits);
        
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

    void SimulationResultWriter::m_saveCsvCells(::std::vector<Cells::Cell> const& cells, uint64_t step) const
    {
        size_t filePathLength = m_option.OutputCsvCellPath().size() + m_digits + 4; // ".csv"
        size_t filePathCapacity = filePathLength + 1;

        // "%s%020llu.csv"
        char optionStr[14];
        
        ::snprintf(optionStr, 14, "%%s0%%%lu.csv", m_digits);
        
        char* filePath = new char[filePathCapacity];

        ::snprintf(filePath, filePathCapacity, optionStr, m_option.OutputCsvCellPath().c_str(), step);

        ::std::ofstream ofs(filePath);
        ofs << ::std::boolalpha;
        
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

    SimulationResultWriter::SimulationResultWriter(SimulationOption option)
        : m_option(::std::move(option))
        , m_digits(s_log10(Settings::Config::Simulation::TotalSteps()))
    {
        m_initialize();
    }

    void SimulationResultWriter::Save(Simulation const& simulation, uint64_t step) const
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

        }

        if (m_option.IsOutputVideo()) {

        }
    }
}