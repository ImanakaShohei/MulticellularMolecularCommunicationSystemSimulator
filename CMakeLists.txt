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
    src/cpp/CellSim.Users.UserMoleculeDiffusionBehavior.cpp
    src/cpp/CellSim.Settings.Config.UserSettings.cpp
    src/cpp/CellSim.Users.UserSimulationModel.cpp
    src/cpp/impl/CellSim.Simulation.cpp
    src/cpp/impl/CellSim.CellAlgorithms.BarnesHut.cpp
    src/cpp/impl/CellSim.CellAlgorithms.CellAlgorithm.cpp
    src/cpp/impl/CellSim.CellAlgorithms.CellList.cpp
    src/cpp/impl/CellSim.CellAlgorithms.NaiveAlgorithm.cpp
    src/cpp/impl/CellSim.Cells.Cell.cpp
    src/cpp/impl/CellSim.Cells.CellBehaviorPtr.cpp
    src/cpp/impl/CellSim.Cells.NormalCellBehavior.cpp
    src/cpp/impl/CellSim.Cli.CliMain.cpp
    src/cpp/impl/CellSim.Cli.ParameterOption.cpp
    src/cpp/impl/CellSim.Imaging.ImageCreater.cpp
    src/cpp/impl/CellSim.Model.CellGrowthModel.cpp
    src/cpp/impl/CellSim.Model.CellSimulationModel.cpp
    src/cpp/impl/CellSim.Model.ClusterFormationModel.cpp
    src/cpp/impl/CellSim.Model.ClusterRotationModel.cpp
    src/cpp/impl/CellSim.Model.ClusterSproutingModel.cpp
    src/cpp/impl/CellSim.Model.NetworkFormationModel.cpp
    src/cpp/impl/CellSim.Model.WavePropagationModel.cpp
    src/cpp/impl/CellSim.Molecular.Molecule.cpp
    src/cpp/impl/CellSim.Molecular.MoleculeDiffusionBehavior.cpp
    src/cpp/impl/CellSim.Molecular.MoleculeField.cpp
    src/cpp/impl/CellSim.Molecular.NormalMoleculeDiffusionBehavior.cpp
    src/cpp/impl/CellSim.Settings.Config.cpp
    src/cpp/impl/CellSim.Settings.Config.Cell.cpp
    src/cpp/impl/CellSim.Settings.Config.CellAlgorithm.cpp
    src/cpp/impl/CellSim.Settings.Config.CellAlgorithm.CellList.cpp
    src/cpp/impl/CellSim.Settings.Config.Optimization.cpp
    src/cpp/impl/CellSim.Settings.Config.Simulation.cpp
    src/cpp/impl/CellSim.Settings.Config.SimulationModel.cpp
    src/cpp/impl/CellSim.Settings.Config.SimulationModel.ClusterFormation.cpp
    src/cpp/impl/CellSim.Settings.Config.SimulationModel.NetworkFormation.cpp
    src/cpp/impl/CellSim.Threading.StlThreadPool.cpp
    src/cpp/impl/CellSim.Threading.ThreadPool.cpp
)

# ターゲット名は'cellsim'
add_executable(cellsim ${SOURCES})

# 追加のオプション
target_compile_options(cellsim PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8> # MSVCはデフォルトでANSIになるのでUTF-8に変更
    #$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2>
    #$<$<AND:$<NOT:$<CXX_COMPILER_ID:MSVC>>,$<CONFIG:Release>>:-O2>
)

# OpenCVの取得に使う
include(FetchContent)

# OpenCVのURLからデータを取得
FetchContent_Declare(
    opencv
    GIT_REPOSITORY https://github.com/opencv/opencv.git
    GIT_TAG        "4.11.0"
)

# 明示的にビルドオプションを設定（不要ならコメントアウトしてもOK）
# Chat-GPTのコピペだよ
set(BUILD_LIST core,imgproc,highgui,imgcodecs CACHE STRING "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_PERF_TESTS OFF CACHE BOOL "" FORCE)

# よくわからんやつ
FetchContent_MakeAvailable(opencv)

# OpenCVライブラリとリンク
# Chat-GPTのコピペだよ
target_link_libraries(cellsim PRIVATE opencv_core opencv_highgui opencv_imgcodecs opencv_imgproc)

# 追加のincludeパス
target_include_directories(cellsim PRIVATE
    ${CMAKE_SOURCE_DIR}/src/cpp/thirdparty
)