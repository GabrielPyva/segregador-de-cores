#include "hisCalculator.hpp" // Ensure filename matches exactly
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

HistCalculator::HistCalculator(int h, int s) : hBins(h), sBins(s) {
  this->histSize[0] = h;
  this->histSize[1] = s;
}

void HistCalculator::calculateHhsv(Buffer &ctx) {
  if (ctx.hsvImage.empty())
    return;

  calcHist(&ctx.hsvImage, 1, channels, cv::Mat(), ctx.histogram, 2, histSize,
           ranges, true, false);

  normalize(ctx.histogram, ctx.mlImage, 1.0, 0.0, NORM_L1);

  std::cout << "Histogram calculated. Min/Max values adjusted." << std::endl;
}

void HistCalculator::showHistogram(Buffer &ctx) {
  if (ctx.histogram.empty())
    return;

  Mat dataForDisplay;
  ctx.histogram.copyTo(dataForDisplay);

  if (histImage.empty()) {
    histImage = Mat(histH, histW, CV_8UC3, Scalar(0, 0, 0));
  }

  histImage.setTo(Scalar(0, 0, 0));

  int binW = histW / hBins; // Width of one bin
  int binH = histH / sBins; // Height of one bin

  for (int h = 0; h < hBins; h++) {
    for (int s = 0; s < sBins; s++) {
      float binVal = dataForDisplay.at<float>(h, s);

      int intensity = cvRound(binVal);
      if (intensity < 2)
        continue;

      int x1 = h * binW;
      int y1 = histH - (s * binH);
      int x2 = (h + 1) * binW;
      int y2 = histH - ((s + 1) * binH);

      rectangle(histImage, Point(x1, y1), Point(x2, y2), Scalar::all(intensity),
                FILLED);
    }
  }

  std::cout << "Displaying Histogram..." << std::endl;
  imshow("H-S Histogram", histImage);

  waitKey(30000);
}
