#pragma once

class SimMain final {
    private:

    static int RunAll();
    static int RunCommandLineError();
    static int RunConvert();
    static int RunHelp();
    static int RunOpenMovie();
    static int RunSimulation();

    public:

    static int Run(int argc, char** args);

    SimMain() = delete;
    SimMain(SimMain const&) = delete;

    ~SimMain() = delete;

    SimMain& operator=(SimMain const&) = delete;
};