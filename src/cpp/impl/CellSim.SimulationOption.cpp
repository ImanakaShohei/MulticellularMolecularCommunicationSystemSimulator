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
        , m_outputCsvPath()
        , m_outputImagePath()
    {
        constexpr char pathSeparator = (char)::std::filesystem::path::preferred_separator;

        if (!m_outputPath.ends_with(pathSeparator)) {
            m_outputPath.push_back(pathSeparator);
        }

        ::std::string binPath = "bin";
        ::std::string csvPath = "csv";
        ::std::string imgPath = "images";

        binPath.push_back(pathSeparator);
        csvPath.push_back(pathSeparator);
        imgPath.push_back(pathSeparator);

        m_outputBinaryPath = m_outputBinaryPath + binPath;
        m_outputCsvPath = m_outputBinaryPath + csvPath;
        m_outputImagePath = m_outputBinaryPath + imgPath;
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
        f(m_outputCsvPath, m_isOutputCsv);
        f(m_outputImagePath, m_isOutputImage);
    }

}