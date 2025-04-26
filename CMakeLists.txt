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
    src/SimMain.cpp
    src/SimulationSettings.cpp
    src/UserCell.cpp
    src/UserMoleculeSpace.cpp
    src/UserSimulation.cpp
    src/core/BarnesHut.cpp
    src/core/Cell.cpp
    src/core/CellList.cpp
    src/core/ClusterModel.cpp
    src/core/MoleculeSpace.cpp
    src/core/NaiveAlgorithm.cpp
    src/core/Simulation.cpp
    src/utils/Vec3.cpp
)

# ターゲット名は'SimMain'
add_executable(SimMain ${SOURCES})

# 追加のincludeパス
target_include_directories(SimMain
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

# デフォルトでReleaseビルドにする
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Default build type" FORCE)
endif()

# 最適化オプション
target_compile_options(SimMain PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8> # MSVCはデフォルトでANSIになるのでUTF-8に変更
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2>
    $<$<AND:$<NOT:$<CXX_COMPILER_ID:MSVC>>,$<CONFIG:Release>>:-O2>
)

# OpenMPを検索
# ChatGPTからコピペしたやつだよ
find_package(OpenMP REQUIRED)

# コンパイラにOpenMPオプションを追加
# ChatGPTからコピペしたやつだよ
if(OpenMP_CXX_FOUND)
    target_compile_options(SimMain PRIVATE ${OpenMP_CXX_FLAGS})
    target_link_libraries(SimMain PRIVATE ${OpenMP_CXX_LIBRARIES})
endif()

# ビルド後にconfig.yamlをコピー
# ついでにconvert_toolsもコピー
add_custom_command(TARGET SimMain POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/src/config.yaml
            $<TARGET_FILE_DIR:SimMain>/config.yaml
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/convert_tools
            $<TARGET_FILE_DIR:SimMain>/convert_tools
)

# yaml-cppの取得に使う
include(FetchContent)

# yaml-cppのURLからデータを取得
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG        0.8.0
)

# よくわからんやつ
FetchContent_MakeAvailable(yaml-cpp)

# yaml-cppをリンク
target_link_libraries(SimMain PRIVATE yaml-cpp)