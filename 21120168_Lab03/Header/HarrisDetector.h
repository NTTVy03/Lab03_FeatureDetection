#pragma once

#include "KeyPoint.h"
#include "ImageHelper.h"
#include "KernelHelper.h"
#include "DetectorHelper.h"

#include "opencv2/core.hpp"
#include <vector>

using namespace cv;
using namespace std;

class HarrisDetector
{
private:

public:
	void detect(Mat image, vector<mKeyPoint> &keyPoints, Mat &output);
	void detectAndShow(Mat image);

private:
	void calculateGradients(const Mat& source, Mat& Gx, Mat& Gy, Mat& Gxx, Mat& Gyy, Mat& Gxy);
	Mat calculateDet(const Mat& Gxx, const Mat& Gyy, const Mat& Gxy);
	Mat calculateTrace(const Mat& Gxx, const Mat& Gyy);
	Mat calculateR(const Mat& det, const Mat& trace, int k = 0.05);
};

