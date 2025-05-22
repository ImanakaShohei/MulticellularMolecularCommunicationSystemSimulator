/**
 * @file SimMain.cpp
 * @author Takanori Saiki
 * @brief main関数
 * @version 0.1
 * @date 2022-04-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "core/base.hpp"
#include "SimMain.hpp"
#include "SimulationSettings.hpp"
#include "core/Simulation.hpp"
#include <string_view>
#include <filesystem>

int SimMain::Run(int argc, char** args)
{
    using namespace std;
    
    if (argc != 2) return RunCommandLineError();
    
    string_view view = args[1];

    if (view == "all"sv)     return RunAll();
    if (view == "clean"sv)   return RunClean();
    if (view == "convert"sv) return RunConvert();
    if (view == "help"sv)    return RunHelp();
    if (view == "open"sv)    return RunOpenMovie();
    if (view == "run"sv)     return RunSimulation();

    fprintf(stderr, "Unknown option: '%s'\n", args[1]);
    fputs("Run './SimMain help' for all supported options.\n", stderr);

    return 1;
}

int SimMain::RunAll()
{
    int result;

    result = RunSimulation();

    if (result != 0) return result;

    result = RunConvert();

    if (result != 0) return result;

    return RunOpenMovie();
}

int SimMain::RunClean()
{
    auto deletePath = [] (const char* path) {
        ::std::filesystem::path p = path;

        if (!::std::filesystem::exists(p)) return;

        if (::std::filesystem::is_directory(p)) {
            ::std::filesystem::remove_all(p);
        }
        else {
            ::std::filesystem::remove(p);
        }
    };

    try {
        deletePath("./result/");
        deletePath("./molecule_result/");
        deletePath("./image/");
        deletePath("./video/");
        deletePath("./config.txt");
    }
    catch (::std::exception& e) {
        ::std::cerr << "Filesystem error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

int SimMain::RunCommandLineError()
{
    fputs("Invalid number of command-line arguments: exactly 2 expected.\n", stderr);
    fputs("Run './SimMain help' for all supported options.\n", stderr);

    return 1;
}

int SimMain::RunConvert()
{
    puts("Converting result...");
    int result = ::system("python3 convert_tools/draw_colormap_cell.py");

    if (result != 0) return result;

    puts("Creating video...");
    return ::system("python3 convert_tools/img2video.py");
}

int SimMain::RunHelp()
{
    puts("Usage");
    putchar('\n');

    puts("  ./SimMain [option]");
    putchar('\n');

    puts("Options");
    puts("  clean   = Remove result data.");
    puts("  convert = Convert from simulation's result to mp4.");
    puts("  help    = Print help.");
    puts("  open    = Open out.mp4.");
    puts("  run     = Run simulation.");

    return 0;
}

int SimMain::RunOpenMovie()
{
#if SIM_ENV_WINDOWS
    return ::system("start \"\" \".\\video\\out.mp4\"");
#elif SIM_ENV_APPLE
    return ::system("open ./video/out.mp4");
#elif SIM_ENV_UNIX
    return ::system("xdg-open ./video/out.mp4");
#else
    puts("This option \"open\" is not supported on this platform.");
    return 1;
#endif
}

int SimMain::RunSimulation()
{
    bool res = SimulationSettings::init_settings();

    if (!res) {
        std::cout << "Failed to initialize settings." << std::endl;
        return -1;
    }

    Simulation sim;

    sim.exportConfig();
    sim.initCells();
    sim.initDirectories();

    int32_t simResult = sim.run();

    return simResult;
}