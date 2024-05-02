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
            double value = abs(source.at<double>(i,j));

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

void DetectorHelper::getInterestPoint(const vector<Mat>& layers, vector<mKeyPoint>& keyPoints)
{
    // is maxima in 3x3x3
    int nLayers = layers.size();
    int row = layers[0].rows;
    int col = layers[0].cols;

    vector<double> thresholds;

    for (int l = 1; l < nLayers - 1; l++) {
        double threshold = 0.8 * DetectorHelper::getMaxInMat(layers[l]);
        thresholds.push_back(threshold);
    }
    
    for (int l = 1; l < nLayers - 1; l++) {
        for (int r = 1; r < row - 1; r++) {
            for (int c = 1; c < col - 1; c++) {
                if (DetectorHelper::checkMaxima333(layers, l, r, c, thresholds[l])) {
                    keyPoints.push_back(mKeyPoint(r, c, layerToScale(l)));
                }
            }
        }
    }
}

bool DetectorHelper::checkMaxima333(const vector<Mat>& layers, int l, int r, int c, double threshold)
{
    // source size
    int nLayers = layers.size();
    int row = layers[0].rows;
    int col = layers[0].cols;

    double value = abs(layers[l].at<double>(r, c));

    // check neighbours
    for (int dl = -1; dl <= 1; dl++) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0 && dl == 0) continue;

                int nc = c + dx;
                int nr = r + dy;
                int nl = l + dl;

                if (checkInBound(nr, nc, row, col)) {
                    double nValue = layers[nl].at<double>(nr, nc);
                    if (abs(nValue) >= value) {
                        return false;
                    }
                }
            }
        }
    }

    return value > threshold;
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
            if (abs(nValue) >= abs(value)) {
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

double DetectorHelper::layerToScale(int layer)
{
    //return pow(sqrt(2), (layer + 1));
    return sqrt(2) * (layer + 1);

}
