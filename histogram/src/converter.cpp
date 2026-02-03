#include "converter.hpp"
#include <imageCapturer.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

Converter::Converter(int code) : bayerCode(code) {}

void Converter::process(Buffer &ctx) {
  if (ctx.rgbImage.empty())
    return;

  cvtColor(ctx.rgbImage, ctx.hsvImage, COLOR_BGR2HSV);
}
