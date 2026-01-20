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

  // 1. Calculate Histogram
  // Note: Use 'true' for uniform, 'false' for accumulate
  calcHist(&ctx.hsvImage, 1, channels, cv::Mat(), ctx.histogram, 2, histSize,
           ranges, true, false);

  // 2. Normalize for ML (Probability Distribution 0.0 - 1.0)
  // This is great for AI, but invisible to human eyes (values are too small)
  // normalize(ctx.histogram, ctx.histogram, 1.0, 0.0, NORM_L1);

  std::cout << "Histogram calculated. Min/Max values adjusted." << std::endl;
}

void HistCalculator::showHistogram(Buffer &ctx) {
  if (ctx.histogram.empty())
    return;

  // --- STEP 1: PREPARE DATA ---
  // Create a temporary clone to normalize for DISPLAY (0 - 255)
  // We do NOT want to change ctx.histogram because the AI needs the original
  // values.
  Mat dataForDisplay;
  ctx.histogram.copyTo(dataForDisplay);

  // Normalize to 0-255 so we can actually see it
  normalize(dataForDisplay, dataForDisplay, 0, 255, NORM_MINMAX);

  // --- STEP 2: PREPARE CANVAS ---
  // Use 'histImage' (the 512x400 Mat defined in your header)
  // If you haven't initialized it in the constructor/header, do it here:
  if (histImage.empty()) {
    histImage = Mat(histH, histW, CV_8UC3, Scalar(0, 0, 0));
  }

  // Clear the background to black
  histImage.setTo(Scalar(0, 0, 0));

  // --- STEP 3: DRAW ---
  int binW = histW / hBins; // Width of one bin
  int binH = histH / sBins; // Height of one bin

  for (int h = 0; h < hBins; h++) {
    for (int s = 0; s < sBins; s++) {
      // READ from the 0-255 normalized data
      float binVal = dataForDisplay.at<float>(h, s);

      // If the value is basically 0, skip drawing to save time
      int intensity = cvRound(binVal);
      if (intensity < 2)
        continue;

      // Calculate coordinates
      // Note: In images, Y=0 is top. We usually want S=0 at the bottom.
      int x1 = h * binW;
      int y1 = histH - (s * binH);
      int x2 = (h + 1) * binW;
      int y2 = histH - ((s + 1) * binH);

      // Draw on the CANVAS (histImage), not the data matrix
      rectangle(histImage, Point(x1, y1), Point(x2, y2), Scalar::all(intensity),
                FILLED);
    }
  }

  std::cout << "Displaying Histogram..." << std::endl;
  imshow("H-S Histogram", histImage);

  // Wait for 30ms to allow the window to paint.
  // Do NOT use 30000 inside a real-time loop or it will freeze for 30 seconds.
  waitKey(30000);
}
