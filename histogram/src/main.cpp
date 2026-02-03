#include "buffer.hpp"
#include "converter.hpp"
#include "hisCalculator.hpp"
#include "imageCapturer.hpp"
#include <iostream>
#include <opencv2/highgui.hpp>

using namespace std;

int main(int argc, char *argv[]) {
  std::string jsonPath =
      "/home/daniel/Work/segregador-de-cores/histogram/images/imagesPaths.json";

  ImageCapturer capturer(0, jsonPath);
  Buffer buffer;

  Converter converter(cv::COLOR_BayerBG2BGR);

  HistCalculator calculator(180, 256);

  cv::namedWindow("Debug Window", cv::WINDOW_NORMAL);

  std::cout << "Starting loop..." << std::endl;

  while (true) {
    bool gotFrame = capturer.getFrame(buffer.rgbImage);

    if (!gotFrame) {
      std::cout << "Camera failed, trying JSON images..." << std::endl;
      ifstream file(jsonPath);
      Json::Value root;
      file >> root;
      for (const auto &imagePath : root["images"]) {
        std::cout << "Image Path: " << imagePath.asString() << std::endl;
        buffer.rgbImage =
            cv::imread(imagePath.asString(), cv::IMREAD_UNCHANGED);
        cv::imshow("Debug Window", buffer.rgbImage);
        std::cout << "Image Size: " << buffer.rgbImage.size() << std::endl;
        converter.process(buffer);

        calculator.calculateHhsv(buffer);
        calculator.showHistogram(buffer);
        cv::waitKey(0);
      }
      break;
    }
    cv::imshow("Debug Window", buffer.rgbImage);
    std::cout << "Image Size: " << buffer.rgbImage.size() << std::endl;
    cv::waitKey(1);
    converter.process(buffer);

    calculator.calculateHhsv(buffer);
    calculator.showHistogram(buffer);
  }

  return 0;
}
