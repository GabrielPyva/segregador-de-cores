#pragma once
#include "buffer.hpp"
#include "imageCapturer.hpp"
#include <opencv2/opencv.hpp>

class Converter {
private:
  int bayerCode;

public:
  Converter(int code);
  bool process(Buffer &ctx);
};
