#include "target_point.h"
#include <iostream>
#include <cmath>
using namespace std;

TargetPoint::TargetPoint(): x_(0), y_(0)
{
}

TargetPoint::TargetPoint(int x2, int y2): x_(x2), y_(y2)
{
}

int TargetPoint::get_x()
{
	return x_;
}

void TargetPoint::set_x(int x2)
{
	x_ = x2;
}

int TargetPoint::get_y()
{
	return y_;
}

void TargetPoint::set_y(int y2)
{
	y_ = y2;
}

TargetPoint& TargetPoint::get_point()
{
	return *this;
}

int TargetPoint::CalculateDistance(TargetPoint& robot2)
{
	return abs(robot2.get_x() - get_x()) + abs(robot2.get_y() - get_y());
}

bool TargetPoint::MoveNorth()
{
	y_++;
	return true;
}

bool TargetPoint::MoveEast()
{
	x_++;
	return true;
}

bool TargetPoint::MoveWest()
{
	x_--;
	return true;
}

bool TargetPoint::MoveSouth()
{
	y_--;
	return true;
}

TargetPoint TargetPoint::operator+(const TargetPoint& point) const
{
	TargetPoint a;
	a.x_ = x_ + point.x_;
	a.y_ = y_ + point.y_;
	return a;
}

TargetPoint TargetPoint::operator-(const TargetPoint& point) const
{
	TargetPoint a;
	a.x_ = x_ - point.x_;
	a.y_ = y_ - point.y_;
	return a;
}

TargetPoint TargetPoint::operator=(const TargetPoint& point)
{
	x_ = point.x_;
	y_ = point.y_;
	return *this;
}

ostream& operator<<(ostream& stream, const TargetPoint& point)
{
	stream << "(" << point.x_ << ", " << point.y_ << ")";
	return stream;
}

istream& operator>>(istream& stream, TargetPoint& point)
{
	stream >> point.x_ >> point.y_;
	return stream;
}