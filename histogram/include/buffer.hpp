#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

struct Buffer {
  cv::Mat rgbImage, floatImage, hsvImage, histogram;
  std::vector<float> mlVector;
};
