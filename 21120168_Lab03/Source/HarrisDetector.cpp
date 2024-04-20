#include "../Header/HarrisDetector.h"

void HarrisDetector::detect(Mat image, vector<mKeyPoint>& keyPoints, Mat& output)
{
	// 1. Convert to CV_64F &&  Gaussian Blur
	Mat image64;
	ImageHelper::preprocess(image,image64);
	Mat blurImage = ImageHelper::GaussianBlur(image64);

	// 2. Gx, Gy, Gxx = Gx^2, Gyy = Gy^2, Gxy = Gx.Gy
	Mat Gx, Gy, Gxx, Gyy, Gxy;
	calculateGradients(blurImage, Gx, Gy, Gxx, Gyy, Gxy);

	// 3. Gaussian Blur: Gx^2, Gy^2, Gxy
	Gxx = ImageHelper::GaussianBlur(Gxx);
	Gyy = ImageHelper::GaussianBlur(Gyy);
	Gxy = ImageHelper::GaussianBlur(Gxy);

	// 4. calculate R
	// 4.1. det(M) = Gx^2 * Gy^2 - Gxy
	Mat det = calculateDet(Gxx, Gyy, Gxy);

	// 4.2. trace(M) = Gx^2 + Gy^2
	Mat trace = calculateTrace(Gxx, Gyy);

	// 4.3. R = det(M) - k * trace(M)^2; k = 0.05
	Mat R = calculateR(det, trace);
	double maxR = DetectorHelper::getMaxInMat(R);

	// 5. NMS
	Mat NMSMat = DetectorHelper::NMS(R);

	// 6. threshold: threshold * maxR
	float threshold = DEFAULT_THRESHOLD * maxR;
	DetectorHelper::thresholding(NMSMat, threshold, keyPoints);
	
	// 7. show keypoints on source image
	ImageHelper::showPointsInImage(image, keyPoints, output);
}

void HarrisDetector::detectAndShow(Mat image)
{
	// detect
	Mat output;
	vector<mKeyPoint> keyPoints;

	detect(image, keyPoints, output);

	// show images
	// source
	ImageHelper::showImage(image, "Harris - Source");

	// destination
	ImageHelper::showImage(output, "Harris - Destination");
}

void HarrisDetector::calculateGradients(const Mat& source, Mat& Gx, Mat& Gy, Mat& Gxx, Mat& Gyy, Mat& Gxy)
{
	int row = source.rows;
	int col = source.cols;

	Gx = Mat(row, col, CV_64F);
	Gy = Mat(row, col, CV_64F);
	Gxx = Mat(row, col, CV_64F);
	Gxy = Mat(row, col, CV_64F);
	Gyy = Mat(row, col, CV_64F);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			// be careful with the bounding conditions T_T
			double center = source.at<double>(i, j);
			double right = (j+1 < col ? source.at<double>(i, j+1): center);
			double bottom = (i+1 < row ? source.at<double>(i+1, j): center);

			// Gx
			Gx.at<double>(i, j) = right - center;
			// Gy
			Gy.at<double>(i, j) = bottom - center;
			// Gxx = (Gx)^2
			Gxx.at<double>(i, j) = Gx.at<double>(i, j) * Gx.at<double>(i, j);
			// Gyy = (Gy)^2
			Gyy.at<double>(i, j) = Gy.at<double>(i, j) * Gy.at<double>(i, j);
			// Gxy = Gx.Gy
			Gxy.at<double>(i, j) = Gx.at<double>(i, j) * Gy.at<double>(i, j);
		}
	}
}

Mat HarrisDetector::calculateDet(const Mat& Gxx, const Mat& Gyy, const Mat& Gxy)
{
	// det(M) = Gxx * Gyy - Gxy * Gxy
	int row = Gxx.rows;
	int col = Gxx.cols;

	Mat det = Mat(row, col, CV_64F);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			double xx = Gxx.at<double>(i, j);
			double yy = Gyy.at<double>(i, j);
			double xy = Gxy.at<double>(i, j);

			det.at<double>(i, j) = (xx * yy - xy * xy);
		}
	}

	return det;
}

Mat HarrisDetector::calculateTrace(const Mat& Gxx, const Mat& Gyy)
{
	// trace(M) = Gx^2 + Gy^2
	int row = Gxx.rows;
	int col = Gxx.cols;

	Mat trace = Mat(row, col, CV_64F);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			double xx = Gxx.at<double>(i, j);
			double yy = Gyy.at<double>(i, j);

			trace.at<double>(i, j) = (xx + yy);
		}
	}

	return trace;
}

Mat HarrisDetector::calculateR(const Mat& det, const Mat& trace, int k)
{
	// R = det(M) - k * trace(M) ^ 2; k = 0.05
	int row = det.rows;
	int col = det.cols;

	Mat R = Mat(row, col, CV_64F);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			double d = det.at<double>(i, j);
			double t = trace.at<double>(i, j);

			R.at<double>(i, j) = (d - k * t * t);
		}
	}

	return R;
}
