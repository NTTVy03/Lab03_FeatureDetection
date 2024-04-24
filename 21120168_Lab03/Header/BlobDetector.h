#pragma once

#include <vector>
#include "opencv2/core.hpp"

#include "KeyPoint.h"
#include "ImageHelper.h"
#include "Constant.h"
#include "DetectorHelper.h"

using namespace std;
using namespace cv;

class BlobDetector
{
private:

public:
	void detect(Mat image, vector<mKeyPoint>& keyPoints, Mat& output);
	void detectAndShow(Mat image);
};

