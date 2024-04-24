#include "../Header/KeyPoint.h"

mKeyPoint::mKeyPoint(int r, int c, double ra)
{
	_row = r;
	_col = c;
	_radius = ra;
}

int mKeyPoint::row()
{
	return _row;
}

int mKeyPoint::col()
{
	return _col;
}

int mKeyPoint::radius()
{
	return _radius;
}

void mKeyPoint::set(int r, int c, double ra)
{
	_row = r;
	_col = c;
	if (ra != 0)_radius = ra;
}
