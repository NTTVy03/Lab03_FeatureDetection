#pragma once

#define DEFAULT_SIGMA 1.4

#include "opencv2/core.hpp"
#include <iostream>

using namespace std;
using namespace cv;

class KernelHelper
{
private:

public:
	static Mat applyKernel(const Mat& source, const Mat& kernel);
	static Mat generateGaussianKernel(double sigma = DEFAULT_SIGMA);
	static void printKernel(const Mat& kernel);
};

