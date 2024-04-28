#pragma once

#include "HarrisDetector.h"
#include "BlobDetector.h"
#include "DoGDetector.h"

class SIFTDetector
{
private:

public:
	void detectKeypoints(const Mat& source, int detector, vector<mKeyPoint>& keypoints);
private:
	// 1. Detect keypoints
	void detectByDetector(const Mat& source, int detector, vector<mKeyPoint>& keypoints);
	
	// 2. Keypoint localization
	void discardLowcontrast(const Mat& source, vector<mKeyPoint>& keypoints);
	void discardKeypointsOnEdge(const Mat& source, vector<mKeyPoint>& keypoints);

	// 3. Orientation assignment
	void assignOrientation(const Mat& source, vector<mKeyPoint>& keypoints);

	// 4. SIFT construction
	void calculateKeypointDescriptors(const Mat& source, vector<mKeyPoint>& keypoints);
};

