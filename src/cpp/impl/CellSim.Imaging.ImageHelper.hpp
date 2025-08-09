#ifndef CELLSIM_IMAGING_IMAGEHELPER_HPP
#define CELLSIM_IMAGING_IMAGEHELPER_HPP

#include "base.hpp"
#include <opencv2/opencv.hpp>

namespace CellSim::Imaging
{
    class ImageHelper final {
        public:

        CELLSIM_STATIC_CLASS(ImageHelper);

        /// @brief 画像を合成
        /// @param background 背景
        /// @param foreground 前景
        /// @return 
        static ::cv::Mat CombineImages(
            ::cv::Mat const& background,
            ::cv::Mat const& foreground
        );
    };
}

#endif //!CELLSIM_IMAGING_IMAGEHELPER_HPP