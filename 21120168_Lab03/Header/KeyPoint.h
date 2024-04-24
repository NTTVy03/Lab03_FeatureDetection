#pragma once
class mKeyPoint
{
private:
	int _row;
	int _col;
	double _radius;
public:
	mKeyPoint(int r, int c, double ra = 0);

	int row();
	int col();
	int radius();

	void set(int r, int c, double ra = 0);
};

