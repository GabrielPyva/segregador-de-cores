#include <opencv2/opencv.hpp>
#include <vector>

struct Buffer {
  cv::Mat rawImage, rgbImage, floatImage, hsvImage, histogram;
  std::vector<float> mlVector;
};
