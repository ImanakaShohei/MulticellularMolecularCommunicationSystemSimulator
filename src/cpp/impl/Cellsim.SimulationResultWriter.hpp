#ifndef CELLSIM_SIMULATIONRESULTWRITER_HPP
#define CELLSIM_SIMULATIONRESULTWRITER_HPP

#include "base.hpp"
#include "CellSim.SimulationOption.hpp"

namespace CellSim
{
    /// @brief シミュレーション結果の出力
    class SimulationResultWriter {
        private:
        SimulationOption m_option;

        void m_initialize();

        public:

        SimulationResultWriter(SimulationOption const& option);
        SimulationResultWriter(SimulationOption&& option);

        void Save(uint64_t step) const;
    };
}

namespace CellSim
{
    inline void SimulationResultWriter::m_initialize()
    {
        m_option.InitializeDirectories();
    }
}

#endif //!CELLSIM_SIMULATIONRESULTWRITER_HPP