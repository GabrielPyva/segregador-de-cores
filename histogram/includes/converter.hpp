#pragma once
#include "buffer.h"
#include <opencv2/opencv.hpp>
#include <iostream>
 
class Converter {
  private:
    int bayerCode;
  public:
    void imageConverter(code : int);
    bool converter(std::Buffer&);
}
