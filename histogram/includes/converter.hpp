#pragma once
#include "buffer.hpp"
#include <opencv2/opencv.hpp>

class Converter {
private:
  int bayerCode;

public:
  Converter(int code);
  bool converter(Buffer &ctx);
};
