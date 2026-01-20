#include "converter.hpp"
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;
Converter::Converter(int code) : bayerCode(code) { this->bayerCode = code; }

bool Converter::process(Buffer &ctx) {
  // Convert Bayer to RGB
  if (ctx.rawImage.empty())
    return false;

  cvtColor(ctx.rawImage, ctx.rgbImage, this->bayerCode);

  // Convert 16-bit to 32
  ctx.rgbImage.convertTo(ctx.floatImage, CV_32F, 1.0 / 65535.0);

  // Convert RGB to HSV
  cvtColor(ctx.floatImage, ctx.hsvImage, COLOR_BGR2HSV);
  return true;
}
