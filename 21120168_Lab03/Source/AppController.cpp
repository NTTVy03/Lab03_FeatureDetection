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
	// match by SIFT and KNN: <image1> <image2> <detector>
	// detector: 1 (Harris), 2 (Blob), 3 (DoG)
	else if (argc == 4 && checkDetector(argv[3])) {
		// exec matching images
		Mat image1 = ImageHelper::readImage(argv[1]);
		Mat image2 = ImageHelper::readImage(argv[2]);
		int detector = atoi(argv[3]);

		ImagesMatcher* matcher = new ImagesMatcher();
		double result = matcher->matchBySIFT(image1, image2, detector);
		cout << "Matching score: " << result << "\n";
		delete matcher;
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
	cout << "Detect by Harris: 21120168_Lab03.exe <img_path> harris\n";
	cout << "Detect by Blob:   21120168_Lab03.exe <img_path> blob\n";
	cout << "Detect by DoG:    21120168_Lab03.exe <img_path> dog\n";
	cout << "Match 2 images:   21120168_Lab03.exe <img_path1>  <img_path2> <detector>\n";
	cout << "Detector:";
	cout << "\t 1: Harris\n";
	cout << "\t 2: Blob\n";
	cout << "\t 3: DoG\n";
	cout << "-----------------------------------------\n";
}

bool AppController::checkDetector(char* detector)
{
	return (strcmp(detector, "1") == 0 || 
		strcmp(detector, "2") == 0 || 
		strcmp(detector, "3") == 0);
}
