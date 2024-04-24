#include "../Header/DoGDetector.h"

void DoGDetector::detect(Mat image, vector<mKeyPoint>& keyPoints, Mat& output)
{
	// 1. Convert to CV_64F &&  Gaussian Blur
	cout << "Prepocess image...\n";
	Mat image64;
	ImageHelper::preprocess(image, image64);
	Mat blurImage = ImageHelper::GaussianBlur(image64);

	// 2. Create n layer DoG[]
	cout << "Generate layers...\n";
	double sigma = DEFAULT_SIGMA;
	int numberLayers = 10;
	vector<Mat> layers;

	Mat prevGaussianKernel = KernelHelper::generateGaussianKernel(sigma);
	Mat prevGaussianImage = KernelHelper::applyKernel(blurImage, prevGaussianKernel);
	Mat curGaussianKernel;
	Mat curGaussianImage;

	for (int i = 0; i < numberLayers; i++) {
		// 2.1. calculate sigma[i] --> generate Gaussian kernel
		sigma = sigma + 1;
		curGaussianKernel = KernelHelper::generateGaussianKernel(sigma);
		curGaussianImage = KernelHelper::applyKernel(blurImage, curGaussianKernel);

		// 2.2. calculate DoG layer = cur - prev
		layers.push_back(curGaussianImage - prevGaussianImage);
		cout << "layer " << i << "\n";

		// 2.3. swap for next DoG
		prevGaussianImage = curGaussianImage;
	}

	// 3. Find Interset Point (maxima in 3x3x3)
	cout << "Select Key Point...\n";
	DetectorHelper::getInterestPoint(layers, keyPoints);

	// 7. show keypoints on source image
	cout << "Show Interset Point in Image...\n";
	ImageHelper::showPointsInImage(image, keyPoints, output);
}

void DoGDetector::detectAndShow(Mat image)
{
	// detect
	Mat output;
	vector<mKeyPoint> keyPoints;

	detect(image, keyPoints, output);

	// show images
	// source
	ImageHelper::showImage(image, "DoG - Source");

	// destination
	ImageHelper::showImage(output, "DoG - Destination");
}
