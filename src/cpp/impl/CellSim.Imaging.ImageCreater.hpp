#ifndef CELLSIM_IMAGING_IMAGECREATER_HPP
#define CELLSIM_IMAGING_IMAGECREATER_HPP

#include "base.hpp"

#include <vector>

namespace CellSim::Imaging
{
    /// @brief 画像生成
    class ImageCreater final {
        public:

        CELLSIM_STATIC_CLASS(ImageCreater);

        static void SaveAs(Simulation const& simulation, const char* filePath);
        static void SaveAs(::std::vector<Cells::Cell> const& cells);
        static void SaveAs(::std::vector<Cells::Cell> const& cells, ::std::vector<Molecular::MoleculeField> const& molecules);
    };
}

#endif //!CELLSIM_IMAGING_IMAGECREATER_HPP