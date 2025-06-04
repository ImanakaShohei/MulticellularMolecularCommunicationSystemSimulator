#ifndef CELLSIM_SIMULATIONOPTION_HPP
#define CELLSIM_SIMULATIONOPTION_HPP

#include "base.hpp"

#include <string>

namespace CellSim
{
    /// @brief コマンドラインで指定したシミュレーションで使用するオプション
    struct SimulationOption {
        /// @brief データをバイナリファイルとして出力するかどうか
        bool IsOutputBinary;

        /// @brief データをcsvファイルとして出力するかどうか
        bool IsOutputCsv;

        /// @brief データを画像として出力するかどうか
        bool IsOutputImage;

        ::std::string OutputPath;

        
    };
}

#endif //!CELLSIM_SIMULATIONOPTION_HPP