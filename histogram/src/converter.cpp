#include "converter.hpp"
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;
Converter::Converter(int code) : bayerCode(code) { this->bayerCode = code; }

bool Converter::process(Buffer &ctx) {
  // Conversions
  bool state = false;
  if (!ctx.rawImage.empty()) {
    cvtColor(ctx.rawImage, ctx.rgbImage, cv::COLOR_BayerBG2BGR);
    cvtColor(ctx.rgbImage, ctx.hsvImage, cv::COLOR_BGR2HSV);
    state = true;
  } else {
    cerr << "No raw image found in buffer!" << std::endl;
  }
  return state;
}
