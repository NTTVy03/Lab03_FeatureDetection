#pragma once

#include "opencv2/core.hpp"
#include <iostream>

#include "Constant.h"

using namespace std;
using namespace cv;

class KernelHelper
{
private:

public:
	static Mat applyKernel(const Mat& source, const Mat& kernel);
	static Mat generateGaussianKernel(double 
		= DEFAULT_SIGMA);
	static Mat generateLOGKernel(double sigma = DEFAULT_SIGMA);
	static void printKernel(const Mat& kernel);
private:
	static int calculateKernelSize(double sigma);
};

