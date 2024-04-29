#pragma once

#include "opencv2/core.hpp"
#include "KeyPoint.h"
#include "Constant.h"

#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

class DetectorHelper
{
private:
	static const int HIDDEN_COLOR = 0;

public:
	static double getMaxInMat(const Mat& source);
	static Mat NMS(const Mat& source);
	static void thresholding(const Mat& source, double threshold, vector<mKeyPoint>& keyPoints);
	static void getInterestPoint(const vector<Mat>& layers, vector<mKeyPoint>& keyPoints);
	static double layerToScale(int layer);

private:
	static bool checkMaxima(int i, int j, const Mat& source);
	static bool checkMaxima333(const vector<Mat>& layers, int l, int r, int c, double threshold);
	static bool checkInBound(int i, int j, int row, int col);
};

