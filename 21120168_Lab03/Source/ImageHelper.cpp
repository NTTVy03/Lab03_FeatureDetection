#include "../Header/ImageHelper.h"

Mat ImageHelper::readImage(const char* imagePath)
{
    Mat image = imread(imagePath);

    // if image invalid show error and exit
    if (image.empty()) {
        cerr << "Can not read image from the path: " << imagePath << "\n";
        exit(-1);
    }

    return image;
}

void ImageHelper::preprocess(const Mat& source, Mat& destination)
{
    // color --> gray scale
    cvtColor(source, destination, COLOR_BGR2GRAY);
    // CV_8U --> CV_64F
    destination.convertTo(destination, CV_64F);
}

Mat ImageHelper::GaussianBlur(const Mat& source)
{
    // generate Gaussian kernel
    Mat GaussianKernel = KernelHelper::generateGaussianKernel();

    // apply kernel and return
    return KernelHelper::applyKernel(source, GaussianKernel);
}

void ImageHelper::showPointsInImage(const Mat& source, const vector<mKeyPoint>& keyPoints, Mat& output)
{
    // save the original image
    source.copyTo(output);

    int thickness = 2;
    Scalar color = Scalar(0, 0, 255); // RED circle

    for (mKeyPoint k : keyPoints) {
        int radius = (k.radius() == 0 ? 1 : k.radius());
        Point keyPoint = Point(k.col(), k.row()); // convert mKeyPoint to Point (openCV)
        circle(output, keyPoint, radius, color, thickness);
    }
}

/*
void ImageHelper::showCirclesInImage(const Mat& source, const vector<mKeyPoint>& keyPoints, Mat& output)
{
    // save the original image
    source.copyTo(output);

    int radius = 30;
    int thickness = 3;
    Scalar color = Scalar(0,0,255); // RED circle

    for (mKeyPoint k : keyPoints) {
        Point keyPoint = Point(k.col(), k.row()); // convert mKeyPoint to Point (openCV)
        circle(output, keyPoint, radius, color, thickness);
    }
}
*/

void ImageHelper::showImage(const Mat& image, const char* windowName)
{
    Mat imageShow;
    image.convertTo(imageShow, CV_8U);

    // custom window
    namedWindow(windowName, WINDOW_KEEPRATIO);

    // show image
    imshow(windowName, imageShow);
}
