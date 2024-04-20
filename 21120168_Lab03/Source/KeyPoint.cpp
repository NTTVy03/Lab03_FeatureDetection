#include "../Header/KeyPoint.h"

mKeyPoint::mKeyPoint(int r, int c)
{
	_row = r;
	_col = c;
}

int mKeyPoint::row()
{
	return _row;
}

int mKeyPoint::col()
{
	return _col;
}

void mKeyPoint::set(int r, int c)
{
	_row = r;
	_col = c;
}
