# エラーの原因
cmake_minimum_required(VERSION 3.11)

# プロジェクト名
project(MulticellularMolecularCommunicationSystemSimulator)

# C++20を指定
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ここにソースファイルを追加
set(SOURCES
    src/cpp/main.cpp
    src/cpp/CellSim.Users.UserCellAlgorithm.cpp
    src/cpp/CellSim.Users.UserCellBehavior.cpp
    src/cpp/impl/CellSim.Simulation.cpp
    src/cpp/impl/CellSim.Cells.Cell.cpp
    src/cpp/impl/CellSim.Model.CellSimulationModel.cpp
    src/cpp/impl/CellSim.Settings.Cli.CliMain.cpp
    src/cpp/impl/CellSim.Threading.StlThreadPool.cpp
    src/cpp/impl/CellSim.Threading.ThreadPool.cpp
)

# ターゲット名は'cellsim'
add_executable(cellsim ${SOURCES})

# 追加のオプション
target_compile_options(SimMain PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8> # MSVCはデフォルトでANSIになるのでUTF-8に変更
    #$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2>
    #$<$<AND:$<NOT:$<CXX_COMPILER_ID:MSVC>>,$<CONFIG:Release>>:-O2>
)