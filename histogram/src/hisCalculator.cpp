#include "hisCalculator.hpp"

HistCalculator::HistCalculator(int h, int s) : hBins(h), sBins(s) {
  this->histSize[0] = h;
  this->histSize[1] = s;
}

void HistCalculator::calculateHhsv(Buffer &ctx) {
  if (ctx.hsvImage.empty())
    return; // Safety check

  cv::calcHist(&ctx.hsvImage, 1, channels, cv::Mat(), ctx.histogram, 2,
               histSize, ranges, true, false);
}
