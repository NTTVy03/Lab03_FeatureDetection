#include "../Header/SIFT.h"

void SIFTDetector::detectKeypoints(const Mat& source, int detector, vector<mKeyPoint>& keypoints)
{
	// 1. Detect keypoints with detector (1: Harris, 2: Blob, 3: DoG)
	detectByDetector(source, detector, keypoints);

	// 2. Keypoint localization
	
	// 2.1. Discarding low-contrast keypoints (The Taylor Series Expansion)
	discardLowcontrast(source, keypoints);

	// 2.2. Discarding keypoints on edges (Principal Curvatures)
	discardKeypointsOnEdge(source, keypoints);

	// 3. Orientation assignment
	assignOrientation(source, keypoints);
	
	// 4. SIFT construction - keypoint descriptor
	calculateKeypointDescriptors(source, keypoints);
}

void SIFTDetector::detectByDetector(const Mat& source, int detector, vector<mKeyPoint>& keypoints)
{
	// output: save in keypoints
	// keypoint = (x,y,scale)
}

void SIFTDetector::discardLowcontrast(const Mat& source, vector<mKeyPoint>& keypoints)
{
	// The Taylor Series Expansion
	// output: reduce the number of keypoints
}

void SIFTDetector::discardKeypointsOnEdge(const Mat& source, vector<mKeyPoint>& keypoints)
{
	// Principal Curvatures
	// output: reduce the number of keypoints
}

void SIFTDetector::assignOrientation(const Mat& source, vector<mKeyPoint>& keypoints)
{
	// 3.1. Calculate Gradient (magnitude, orientation)

	// 3.2. Orientation histogram

	// 3.3. Select peak of histogram
	// --> keypoint = (x,y,scale,orientation)
}

void SIFTDetector::calculateKeypointDescriptors(const Mat& source, vector<mKeyPoint>& keypoints)
{
	// 4.1. Create window 16x16 around each keypoint
	// --> 4x4 subregions

	// 4.2. Calculate orientation histogram for each subregion
	// --> (4x4) subregions x 8 directions = 128-dimentional feature vector
	//  --> keypoint = (x,y,scale,orientation,descriptor)
}
