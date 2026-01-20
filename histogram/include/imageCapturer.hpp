#pragma once
#include <fstream>
#include <json/json.h> // Ensure you have libjsoncpp-dev installed
#include <opencv2/opencv.hpp>
#include <string>

class ImageCapturer {
private:
  int cameraIndex;
  cv::VideoCapture cap; // Camera stays OPEN here
  std::string imagesJson;

public:
  ImageCapturer(int camIndex, const std::string &jsonFile);
  ~ImageCapturer(); // Destructor to close camera

  // Returns true if a frame was grabbed
  bool getFrame(cv::Mat &outputFrame);

  // Returns true if image loaded
  bool getImage(cv::Mat &outputFrame);
};
