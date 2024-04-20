#include "../Header/AppController.h"

void AppController::run(int argc, char** argv)
{
	// Harris: <img> harris
	if (argc == 3 && strcmp(argv[2], HARRIS) == 0) {
		// exec Harris
		Mat image = ImageHelper::readImage(argv[1]);

		HarrisDetector* detector = new HarrisDetector();
		detector->detectAndShow(image);
		delete detector;
	}
	// Blob: <img> blob
	else if (argc == 3 && strcmp(argv[2], BLOB) == 0) {
		// exec Blob
		Mat image = ImageHelper::readImage(argv[1]);

		BlobDetector* detector = new BlobDetector();
		detector->detectAndShow(image);
		delete detector;
	}
	// DoG: <img> dog
	else if (argc == 3 && strcmp(argv[2], DOG) == 0) {
		// exec DoG
		Mat image = ImageHelper::readImage(argv[1]);

		DoGDetector* detector = new DoGDetector();
		detector->detectAndShow(image);
		delete detector;
	}
	// match by SIFT
	else if (false) {
		// exec matching images by SIFT
	}
	// show Help
	else {
		showHelp();
	}

	waitKey();
}

void AppController::showHelp()
{
	cout << "---------------- LAB 03 ----------------\n";
	cout << "Detect by Harris: 21120168_Lab03 <img_path> harris\n";
	cout << "Detect by Blob:   21120168_Lab03 <img_path> blob\n";
	cout << "Detect by DoG:    21120168_Lab03 <img_path> dog\n";
	cout << "Match 2 images:   21120168_Lab03 <img_path1>  <img_path2> <detector>\n";
	cout << "Detector:";
	cout << "\t 1: Harris\n";
	cout << "\t 2: Blob\n";
	cout << "\t 3: DoG\n";
	cout << "-----------------------------------------\n";
}
