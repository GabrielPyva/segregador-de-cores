#include "hisCalculator.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/highgui.hpp>

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
  normalize(ctx.histogram, ctx.histogram, 1.0, 0.0, NORM_L1);
}

void HistCalculator::showHistogram(Buffer &ctx) {
  Mat displayHist = ctx.histogram.clone();

  normalize(displayHist, displayHist, 0, 255, NORM_MINMAX);

  displayHist.setTo(Scalar(0, 0, 0));

  for (int h = 0; h < hBins; h++) {
    for (int s = 0; s < sBins; s++) {
      float binVal = ctx.histogram.at<float>(h, s);
      int intensity = cvRound(binVal);
      rectangle(displayHist,
                Point(h * histW / hBins, histH - s * histH / sBins),
                Point((h + 1) * histW / hBins, histH - (s + 1) * histH / sBins),
                Scalar::all(intensity), FILLED);
    }
  }

  imshow("H-S Histogram", displayHist);
  waitKey(1);
}
