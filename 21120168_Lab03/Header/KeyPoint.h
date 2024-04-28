#pragma once

#include <vector>

using namespace std;

class mKeyPoint
{
private:
	int _row;
	int _col;
	double _scale;
	double _orientation;
	vector<double> _descriptors;
public:
	mKeyPoint(int r, int c, double s = 0);

	int row();
	int col();
	double scale();
	int radius();

	void set(int r, int c, double s = 0);
};

