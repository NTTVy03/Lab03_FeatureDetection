#include "../Header/ImageHelper.h"

Mat ImageHelper::readImage(const char* imagePath)
{
    // add code read image (gray scale)
    Mat image = imread(imagePath, IMREAD_GRAYSCALE);

    // if image invalid show error and exit
    if (image.empty()) {
        cerr << "Can not read image from the path: " << imagePath << "\n";
        exit(-1);
    }

    return image;
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

    int radius = 30;
    Scalar color = Scalar(255,0,0); // RED circle

    for (mKeyPoint k : keyPoints) {
        Point keyPoint = Point(k.col(), k.row()); // convert mKeyPoint to Point (openCV)
        circle(output, keyPoint, radius, color);
    }
}

void ImageHelper::showImage(const Mat& image, const char* windowName)
{
    // custom window
    namedWindow(windowName, WINDOW_KEEPRATIO);

    // show image
    imshow(windowName, image);
}
