#include <opencv2/opencv.hpp>
#include <vector>

class Buffer {
public:
  struct BufferData {
    cv::Mat rawImage;
    cv::Mat rgbImage;
    cv::Mat floatimage;
    cv::Mat hsvImage;
    cv::Mat histogram;
    std::vector<float> mlVector;
  };
};
