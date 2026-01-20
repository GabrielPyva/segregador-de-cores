#include <imageCapturer.hpp>

using namespace cv;
using namespace std;

ImageCapturer::ImageCapturer(int camIndex, string const &jsonFile)
    : cameraIndex(camIndex), frameCounter(0), imagesJson(jsonFile) {}

Mat ImageCapturer::sendFrame() {
  VideoCapture cap(cameraIndex);
  if (!cap.isOpened()) {
    cerr << "Error: Could not open camera." << endl;
    return Mat();
  }

  Mat frame;
  cap >> frame;
  if (frame.empty()) {
    cerr << "Error: Could not read frame." << endl;
    return Mat();
  }

  frameCounter++;
  return frame;
}

Mat ImageCapturer::sendImages() {
  ifstream file(imagesJson);
  if (!file.is_open()) {
    cerr << "Error: Could not open JSON file." << endl;
    return Mat();
  }

  Json::Value root;
  file >> root;
  file.close();

  vector<Mat> images;
  for (const auto &imagePath : root["images"]) {
    Mat img = imread(imagePath.asString());
    if (img.empty()) {
      cerr << "Error: Could not read image " << imagePath.asString() << endl;
      continue;
    }
    images.push_back(img);
  }

  if (images.empty()) {
    cerr << "Error: No valid images found." << endl;
    return Mat();
  }

  // For simplicity, return the first image
  return images[0];
}
