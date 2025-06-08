#include "Cellsim.SimulationResultWriter.hpp"

namespace CellSim
{
    SimulationResultWriter::SimulationResultWriter(SimulationOption const& option)
        : m_option(option)
    {
        m_initialize();
    }

    SimulationResultWriter::SimulationResultWriter(SimulationOption&& option)
        : m_option(::std::move(option))
    {
        m_initialize();
    }

    void SimulationResultWriter::Save(uint64_t step) const
    {
        if (m_option.IsOutputBinary()) {

        }

        if (m_option.IsOutputCsv()) {

        }

        if (m_option.IsOutputImage()) {

        }

        if (m_option.IsOutputVideo()) {

        }
    }
}