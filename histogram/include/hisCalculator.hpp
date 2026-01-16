#pragma once
#include "buffer.hpp"
#include <opencv2/opencv.hpp>

class HistCalculator {
private:
  int hBins;
  int sBins;
  int histSize[2] = {hBins, sBins};
  const float hRanges[2] = {0, 179};
  const float sRanges[2] = {0, 255};
  const float *ranges[2] = {hRanges, sRanges};
  const int channels[2] = {0, 1};

public:
  HistCalculator(int h, int s);
  void calculateHhsv(Buffer &ctx);
};
