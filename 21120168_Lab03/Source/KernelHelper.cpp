#include "../Header/KernelHelper.h"

Mat KernelHelper::applyKernel(const Mat& source, const Mat& kernel)
{
    Mat destination;
    destination.create(source.size(), source.type());

    int border = (kernel.rows - 1) / 2;

    cv::Mat paddedsource;
    cv::copyMakeBorder(source, paddedsource, border, border, border, border, cv::BORDER_REPLICATE);

    for (int y = 0; y < source.rows; ++y) {
        for (int x = 0; x < source.cols; ++x) {
            double sum = 0.0;

            for (int i = 0; i < kernel.rows; ++i) {
                for (int j = 0; j < kernel.cols; ++j) {
                    sum += paddedsource.at<double>(y + i, x + j) * kernel.at<double>(i, j);

                }
            }

            destination.at<double>(y, x) = sum;
        }
    }

    return destination;
}

Mat KernelHelper::generateGaussianKernel(double sigma)
{
    int kernelSize = sigma * 6;
    if (kernelSize % 2 == 0) { // size must be an odd
        kernelSize--;
    }

    int halfKernelSize = kernelSize / 2;
    double sum = 0.0;
    Mat kernel = Mat(kernelSize, kernelSize, CV_64F);

    for (int i = -halfKernelSize; i <= halfKernelSize; ++i)
    {
        for (int j = -halfKernelSize; j <= halfKernelSize; ++j)
        {
            double value = std::exp(-(i * i + j * j) / (2 * sigma * sigma));
            kernel.at<double>(i + halfKernelSize, j + halfKernelSize) = value;
            sum += value;
        }
    }
    kernel /= sum;

    return kernel;
}
