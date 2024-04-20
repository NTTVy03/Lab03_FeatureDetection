#pragma once
class mKeyPoint
{
private:
	int _row;
	int _col;
public:
	mKeyPoint(int r, int c);

	int row();
	int col();

	void set(int r, int c);
};

