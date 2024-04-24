#pragma once

#include "opencv2/core.hpp"
#include <vector>

#include "KeyPoint.h"
#include "ImageHelper.h"
#include "DetectorHelper.h"

using namespace std;
using namespace cv;

class DoGDetector
{
private:

public:
	void detect(Mat image, vector<mKeyPoint>& keyPoints, Mat& output);
	void detectAndShow(Mat image);
};
