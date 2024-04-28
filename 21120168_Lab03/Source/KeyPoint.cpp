#include "../Header/KeyPoint.h"

mKeyPoint::mKeyPoint(int r, int c, double s)
{
	_row = r;
	_col = c;
	_scale = s;
}

int mKeyPoint::row()
{
	return _row;
}

int mKeyPoint::col()
{
	return _col;
}

double mKeyPoint::scale()
{
	return _scale;
}

int mKeyPoint::radius()
{
	return (1.0*_scale * sqrt(2));
}

void mKeyPoint::set(int r, int c, double s)
{
	_row = r;
	_col = c;
	if (s != 0) _scale = s;
}
