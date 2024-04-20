#include "../Header/DetectorHelper.h"

double DetectorHelper::getMaxInMat(const Mat& source)
{
    // find max value in a mat (source)
    int row = source.rows;
    int col = source.cols;

    double maxValue = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            // double instead of CV_64F
            double value = source.at<double>(i,j);

            if (value > maxValue) {
                maxValue = value;
            }
        }
    }

    return maxValue;
}

Mat DetectorHelper::NMS(const Mat& source)
{
    // set non-maxima pixel to BLACK
    int row = source.rows;
    int col = source.cols;

    // create a Mat with same size with source
    Mat output = Mat(row, col, CV_64F);

    // NMS
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (checkMaxima(i, j, source)) {
                output.at<double>(i, j) = source.at<double>(i, j);
            }
            else {
                output.at<double>(i, j) = HIDDEN_COLOR;
            }
        }
    }

    return output;
}

void DetectorHelper::thresholding(const Mat& source, double threshold, vector<mKeyPoint>& keyPoints)
{
    // pixel >= threshold -->  keyPoints
    int row = source.rows;
    int col = source.cols;

    // thresholding
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            double value = source.at<double>(i, j);
            if (value >= threshold) {
                keyPoints.push_back(mKeyPoint(i, j));
            }
        }
    }
}

bool DetectorHelper::checkMaxima(int i, int j, const Mat& source)
{
    // source size
    int row = source.rows;
    int col = source.cols;
    double value = source.at<double>(i, j);

    // neighbours
    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, 1, -1};
    int numNeighbours = dx.size();

    // check neighbours
    for (int t = 0; t < numNeighbours; t++) {
        int ni = i + dx[t];
        int nj = j + dy[t];

        if (checkInBound(ni, nj, row, col)) {
            double nValue = source.at<double>(ni, nj);
            if (nValue > value) {
                return false;
            }
        }
    }

    return true;
}

bool DetectorHelper::checkInBound(int i, int j, int row, int col)
{
    return (i >= 0 && j >= 0 && i < row&& j < col);
}
