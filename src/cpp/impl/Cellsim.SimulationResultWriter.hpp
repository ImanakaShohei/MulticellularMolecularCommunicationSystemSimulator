#ifndef CELLSIM_SIMULATIONRESULTWRITER_HPP
#define CELLSIM_SIMULATIONRESULTWRITER_HPP

#include "base.hpp"
#include "CellSim.SimulationOption.hpp"

#include <vector>

namespace CellSim
{
    /// @brief シミュレーション結果の出力
    class SimulationResultWriter {
        private:
        static constexpr uint32_t s_log10(uint64_t step) noexcept;
        SimulationOption m_option;

        /// @brief ステップ数の桁数
        uint32_t m_digits;

        void m_initialize();

        void m_saveBinaryCells(::std::vector<Cells::Cell> const& cells, uint64_t step) const;
        void m_saveBinaryMolecules(::std::vector<Molecular::MoleculeField> const& cells, uint64_t step) const;
        void m_saveCsvCells(::std::vector<Cells::Cell> const& cells, uint64_t step) const;
        void m_saveCsvMolecules(::std::vector<Molecular::MoleculeField> const& cells, uint64_t step) const;
        void m_saveImages(::std::vector<Molecular::MoleculeField> const& cells, uint64_t step) const;

        public:

        SimulationResultWriter(SimulationOption option);

        void Save(Simulation const& simulation, uint64_t step) const;
    };
}

namespace CellSim
{
    constexpr uint32_t SimulationResultWriter::s_log10(uint64_t step) noexcept
    {
        if (step == 0) [[unlikely]] return 1;

        uint32_t result = 0;

        while (step != 0) {
            step /= 10;
            ++result;
        }

        return result;
    }

    inline void SimulationResultWriter::m_initialize()
    {
        m_option.InitializeDirectories();
    }
}

#endif //!CELLSIM_SIMULATIONRESULTWRITER_HPP