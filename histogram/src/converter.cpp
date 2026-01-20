#include "converter.hpp"
#include <imageCapturer.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

Converter::Converter(int code) : bayerCode(code) {}

void Converter::process(Buffer &ctx) {
  if (ctx.rgbImage.empty())
    return; // Safety check

  // 1. Convert to Float (Scale 0-65535 -> 0.0-1.0)
  // Use the RGB image already sitting in the buffer
  // ctx.rgbImage.convertTo(ctx.floatImage, CV_8U, 1.0 / 255.0);

  // 2. Convert to HSV
  cvtColor(ctx.rgbImage, ctx.hsvImage, COLOR_BGR2HSV);
}
