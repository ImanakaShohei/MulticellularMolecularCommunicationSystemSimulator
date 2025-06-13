#ifndef CELLSIM_SIMULATIONOPTION_HPP
#define CELLSIM_SIMULATIONOPTION_HPP

#include "base.hpp"

#include <string>

namespace CellSim
{
    /// @brief コマンドラインで指定したシミュレーションで使用するオプション
    class SimulationOption {
        private:

        /// @brief データをバイナリファイルとして出力するかどうか
        bool m_isOutputBinary;

        /// @brief データをcsvファイルとして出力するかどうか
        bool m_isOutputCsv;

        /// @brief データを画像として出力するかどうか
        bool m_isOutputImage;

        /// @brief データを動画として出力するかどうか
        bool m_isOutputVideo;

        ::std::string m_outputPath;
        ::std::string m_outputBinaryPath;
        ::std::string m_outputBinaryCellPath;
        ::std::string m_outputBinaryMoleculePath;
        ::std::string m_outputCsvPath;
        ::std::string m_outputCsvCellPath;
        ::std::string m_outputCsvMoleculePath;
        ::std::string m_outputImagePath;

        public:

        SimulationOption(
            bool isOutputBinary,
            bool isOutputCsv,
            bool isOutputImage,
            bool isOutputVideo,
            ::std::string outputPath
        );

        /// @brief データをバイナリファイルとして出力するかどうか
        [[nodiscard]] constexpr bool IsOutputBinary() const noexcept;

        /// @brief データをcsvファイルとして出力するかどうか
        [[nodiscard]] constexpr bool IsOutputCsv() const noexcept;

        /// @brief データを画像として出力するかどうか
        [[nodiscard]] constexpr bool IsOutputImage() const noexcept;

        /// @brief データを動画として出力するかどうか
        [[nodiscard]] constexpr bool IsOutputVideo() const noexcept;

        [[nodiscard]] constexpr ::std::string const& OutputPath() const noexcept;
        [[nodiscard]] constexpr ::std::string const& OutputBinaryPath() const noexcept;
        [[nodiscard]] constexpr ::std::string const& OutputBinaryCellPath() const noexcept;
        [[nodiscard]] constexpr ::std::string const& OutputBinaryMoleculePath() const noexcept;
        [[nodiscard]] constexpr ::std::string const& OutputCsvPath() const noexcept;
        [[nodiscard]] constexpr ::std::string const& OutputCsvCellPath() const noexcept;
        [[nodiscard]] constexpr ::std::string const& OutputCsvMoleculePath() const noexcept;
        [[nodiscard]] constexpr ::std::string const& OutputImagePath() const noexcept;

        void InitializeDirectories() const;
    };
}

namespace CellSim
{
    constexpr bool SimulationOption::IsOutputBinary() const noexcept
    {
        return m_isOutputBinary;
    }

    constexpr bool SimulationOption::IsOutputCsv() const noexcept
    {
        return m_isOutputCsv;
    }

    constexpr bool SimulationOption::IsOutputImage() const noexcept
    {
        return m_isOutputImage;
    }

    constexpr bool SimulationOption::IsOutputVideo() const noexcept
    {
        return m_isOutputVideo;
    }

    constexpr ::std::string const& SimulationOption::OutputPath() const noexcept
    {
        return m_outputPath;
    }

    constexpr ::std::string const& SimulationOption::OutputBinaryPath() const noexcept
    {
        return m_outputBinaryPath;
    }

    constexpr ::std::string const& SimulationOption::OutputBinaryCellPath() const noexcept
    {
        return m_outputBinaryCellPath;
    }

    constexpr ::std::string const& SimulationOption::OutputBinaryMoleculePath() const noexcept
    {
        return m_outputBinaryMoleculePath;
    }

    constexpr ::std::string const& SimulationOption::OutputCsvPath() const noexcept
    {
        return m_outputCsvPath;
    }

    constexpr ::std::string const& SimulationOption::OutputCsvCellPath() const noexcept
    {
        return m_outputCsvCellPath;
    }

    constexpr ::std::string const& SimulationOption::OutputCsvMoleculePath() const noexcept
    {
        return m_outputCsvMoleculePath;
    }

    constexpr ::std::string const& SimulationOption::OutputImagePath() const noexcept
    {
        return m_outputImagePath;
    }
}

#endif //!CELLSIM_SIMULATIONOPTION_HPP