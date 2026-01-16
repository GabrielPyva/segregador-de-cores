#include "converter.hpp"
#include <opencv2/imgproc.hpp>

Converter::Converter(int code) : bayerCode(code) { this->bayerCode = code; }

bool Converter::process(Buffer &ctx) {
  // Conversions
  bool state = false;
  if (!ctx.rawImage.empty()) {
    cv::cvtColor(ctx.rawImage, ctx.rgbImage, cv::COLOR_BayerBG2BGR);
    cv::cvtColor(ctx.rgbImage, ctx.hsvImage, cv::COLOR_BGR2HSV);
    state = true;
  } else {
    std::cerr << "No raw image found in buffer!" << std::endl;
  }
  return state;
}
