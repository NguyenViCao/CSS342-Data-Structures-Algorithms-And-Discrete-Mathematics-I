#ifndef TARGET_POINT_H_
#define TARGET_POINT_H_
#include <iostream>
#include <string>
using namespace std;

class TargetPoint
{
public:
	//constructor
	TargetPoint();
	TargetPoint(int x2_, int y2_);

	//getters-setters
	int get_x();
	int get_y();
	void set_x(int x);
	void set_y(int y);
	TargetPoint& get_point();

	//verb - action
	int CalculateDistance(TargetPoint&);
	bool MoveNorth();
	bool MoveEast();
	bool MoveWest();
	bool MoveSouth();

	//operator overloading
	TargetPoint operator+(const TargetPoint& point) const;
	TargetPoint operator-(const TargetPoint& point) const;
	TargetPoint operator=(const TargetPoint& point);

	friend ostream& operator<<(ostream& stream, const TargetPoint& point);
	friend istream& operator>>(istream& stream, TargetPoint& point);

private:
	int x_;			//coordinate of the point
	int y_;
};
#endif