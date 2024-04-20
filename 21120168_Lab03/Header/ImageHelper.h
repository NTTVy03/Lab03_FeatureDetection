#pragma once
#include "opencv2/core.hpp"
#include <vector>

#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#include "KeyPoint.h"
#include "KernelHelper.h"

using namespace std;
using namespace cv;

class ImageHelper
{
public:
	static Mat readImage(const char* imagePath);
	static Mat GaussianBlur(const Mat& source);
	static void showPointsInImage(const Mat& source, const vector<mKeyPoint>& keyPoints, Mat& output);
	static void showImage(const Mat& image, const char* windowName);
};

