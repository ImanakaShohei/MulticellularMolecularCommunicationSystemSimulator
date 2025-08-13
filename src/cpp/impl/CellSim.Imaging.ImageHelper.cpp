#include "CellSim.Imaging.ImageHelper.hpp"

namespace CellSim::Imaging
{
    // Gemini生成
    ::cv::Mat ImageHelper::CombineImages(
        ::cv::Mat const& background,
        ::cv::Mat const& foreground
    )
    {
        cv::Mat newData = background.clone(); // 背景画像をコピーして新しいMatを作成
        
        // 2. 前景画像をBGRチャンネルとアルファチャンネル(マスク)に分離
        ::std::vector<cv::Mat> channels;
        ::cv::split(foreground, channels); // 4つのチャンネルに分離
        
        ::cv::Mat foreground_bgr; // 色情報(BGR)を格納するMat
        // 最初の3チャンネル(B,G,R)を結合して色情報のみの画像を再構成
        ::cv::merge(std::vector<cv::Mat>{channels[0], channels[1], channels[2]}, foreground_bgr);
        ::cv::Mat mask = channels[3]; // 4番目のチャンネルがアルファチャンネル(マスク)

        // 3. 背景画像に前景画像を合成
        // 背景画像の左上に前景画像を配置するためのROI(関心領域)を設定
        ::cv::Rect roi(0, 0, foreground_bgr.cols, foreground_bgr.rows);
        
        // copyToのマスク機能を使って合成
        // maskのピクセル値が0でない部分だけがコピーされる
        foreground_bgr.copyTo(newData(roi), mask);

        return newData; // 合成された前景画像を返す
    }
}