#include "../Header/BlobDetector.h"

void BlobDetector::detect(Mat image, vector<mKeyPoint>& keyPoints, Mat& output)
{
	// 1. Convert to CV_64F &&  Gaussian Blur
	cout << "Prepocess image...\n";
	Mat image64;
	ImageHelper::preprocess(image, image64);
	Mat blurImage = ImageHelper::GaussianBlur(image64);

	// 2. Create n layer A[]
	cout << "Generate layers...\n";
	double sigma = DEFAULT_SIGMA;
	int numberLayers = 10;
	vector<Mat> layers;

	for (int i = 0; i < numberLayers; i++) {
		// 2.1. calculate sigma[i] --> generate LOG kernel
		Mat LOGKernel = KernelHelper::generateLOGKernel(sigma);
		sigma = sigma + 1;

		// 2.2. L[i] = image * LOG[i]
		layers.push_back(KernelHelper::applyKernel(blurImage, LOGKernel));
	}

	// 3. Find Interset Point (maxima in 3x3x3)
	cout << "Select Interest Point...\n";
	DetectorHelper::getInterestPoint(layers, keyPoints);

	// 7. show keypoints on source image
	cout << "Show Interest Point in Image...\n";
	ImageHelper::showPointsInImage(image, keyPoints, output);
}

void BlobDetector::detectAndShow(Mat image)
{
	cout << "DETECT & SHOW BY BLOB\n";
	// detect
	Mat output;
	vector<mKeyPoint> keyPoints;

	detect(image, keyPoints, output);

	// show images
	// source
	ImageHelper::showImage(image, "Blob - Source");

	// destination
	ImageHelper::showImage(output, "Blob - Destination");
}
