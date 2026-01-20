#include "imageCapturer.hpp"
#include <iostream>

using namespace cv;
using namespace std;

ImageCapturer::ImageCapturer(int camIndex, string const &jsonFile)
    : cameraIndex(camIndex), imagesJson(jsonFile) {

  cap.open(cameraIndex);
  if (!cap.isOpened()) {
    cerr << "Warning: Could not open camera " << camIndex << endl;
  }
}

ImageCapturer::~ImageCapturer() {
  if (cap.isOpened())
    cap.release();
}

bool ImageCapturer::getFrame(cv::Mat &outputFrame) {
  if (!cap.isOpened())
    return false;

  cap >> outputFrame;
  if (outputFrame.empty()) {
    cerr << "Error: Captured empty frame." << endl;
    return false;
  }
  return true;
}

bool ImageCapturer::getImage(cv::Mat &outputFrame) {
  ifstream file(imagesJson);
  if (!file.is_open()) {
    cerr << "Error: JSON file not found." << endl;
    return false;
  }

  Json::Value root;
  file >> root;

  for (const auto &imagePath : root["images"]) {
    outputFrame = imread(imagePath.asString(), IMREAD_UNCHANGED);
    if (!outputFrame.empty())
      return true;
  }

  return false;
}
