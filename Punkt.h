#pragma once
class Punkt
{
public:
	int x = 0;
	int y = 0;

	Punkt()
	{
		x = 0;
		y = 0;
	}
	Punkt(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	bool operator==(const Punkt& src) const { return (this->x == src.x) && (this->y == src.y); }
	bool operator!=(const Punkt& src) const { return !(*this == src); }
	Punkt operator=(const Punkt& src) { this->x = src.x; this->y = src.y; return *this; }

};