#include "impl/CellSim.Cli.CliMain.hpp"
#include <opencv2/core/utils/logger.hpp>
using namespace CellSim::Cli;

int main(int argc, char** argv)
{
    // うっざい表示を抑制
    ::cv::utils::logging::setLogLevel(::cv::utils::logging::LOG_LEVEL_SILENT);
    return CliMain::Run(argc, argv);
}