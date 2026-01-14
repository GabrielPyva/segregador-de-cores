#pragma once
#include "buffer.hpp"
#include <opencv2/opencv.hpp>

class HistCalculator {
private:
  int hBins;
  int sBins;

public:
  HistCalculator(int h, int s);
  void calculateHhsv(Buffer &ctx);
};
