#include "CellSim.SimulationOption.hpp"

#include <filesystem>

namespace CellSim
{
    SimulationOption::SimulationOption(
        bool isOutputBinary,
        bool isOutputCsv,
        bool isOutputImage,
        bool isOutputVideo,
        ::std::string outputPath
    )
        : m_isOutputBinary(isOutputBinary)
        , m_isOutputCsv(isOutputCsv)
        , m_isOutputImage(isOutputImage)
        , m_isOutputVideo(isOutputVideo)
        , m_outputPath(::std::move(outputPath))
        , m_outputBinaryPath()
        , m_outputBinaryCellPath()
        , m_outputBinaryMoleculePath()
        , m_outputCsvPath()
        , m_outputCsvCellPath()
        , m_outputCsvMoleculePath()
        , m_outputImagePath()
    {
        constexpr char pathSeparator = (char)::std::filesystem::path::preferred_separator;

        if (!m_outputPath.ends_with(pathSeparator)) {
            m_outputPath.push_back(pathSeparator);
        }

        m_outputBinaryPath = m_outputPath + "bin";
        m_outputCsvPath = m_outputPath + "csv";
        m_outputImagePath = m_outputPath + "images";

        m_outputBinaryPath.push_back(pathSeparator);
        m_outputCsvPath.push_back(pathSeparator);
        m_outputImagePath.push_back(pathSeparator);

        m_outputBinaryCellPath = m_outputBinaryPath + "cells";
        m_outputBinaryMoleculePath = m_outputBinaryPath + "molecules";
        m_outputCsvCellPath = m_outputCsvPath + "cells";
        m_outputCsvMoleculePath = m_outputCsvPath + "molecules";

        m_outputBinaryCellPath.push_back(pathSeparator);
        m_outputBinaryMoleculePath.push_back(pathSeparator);
        m_outputCsvCellPath.push_back(pathSeparator);
        m_outputCsvMoleculePath.push_back(pathSeparator);
    }

    void SimulationOption::InitializeDirectories() const
    {
        auto f = [] (::std::filesystem::path const& p, bool create) {
            if (::std::filesystem::exists(p)) {
                ::std::filesystem::remove_all(p);
            }
            if (create) {
                ::std::filesystem::create_directory(p);
            }
        };

        f(m_outputPath, true);
        f(m_outputBinaryPath, m_isOutputBinary);
        f(m_outputBinaryCellPath, m_isOutputBinary);
        f(m_outputBinaryMoleculePath, m_isOutputBinary);
        f(m_outputCsvPath, m_isOutputCsv);
        f(m_outputCsvCellPath, m_isOutputCsv);
        f(m_outputCsvMoleculePath, m_isOutputCsv);
        f(m_outputImagePath, m_isOutputImage);
    }

}