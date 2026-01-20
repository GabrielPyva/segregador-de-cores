#pragma once
#include <buffer.hpp>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

class ImageCapturer {
private:
  int cameraIndex;
  int frameCounter;
  string imagesJson;

public:
  ImageCapturer(int camIndex, const string &jsonFile);
  Mat sendFrame();
  Mat sendImages();
  void saveHsvHistogram(Buffer &ctx);
};
