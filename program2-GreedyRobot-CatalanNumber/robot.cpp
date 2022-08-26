#include "robot.h"
#include <string>
using namespace std;

Robot::Robot() : TargetPoint()
{
	set_x(0);
	set_y(0);
}

Robot::Robot(int x1, int y1) : TargetPoint(x1, y1)
{
	set_x(x1);
	set_y(y1);
}

void Robot::set_distance(int d)
{
	distance_ = d;
}

int Robot::distance()
{
	return distance_;
}

Robot& Robot::MoveNorth()
{
	TargetPoint::MoveNorth();
	return *this;
}

Robot& Robot::MoveEast()
{
	TargetPoint::MoveEast();
	return *this;
}

Robot& Robot::MoveWest()
{
	TargetPoint::MoveWest();
	return *this;
}

Robot& Robot::MoveSouth()
{
	TargetPoint::MoveSouth();
	return *this;
}

Robot& Robot::operator=(Robot& robot2)
{
	set_x(robot2.get_x());
	set_y(robot2.get_y());
	return *this;
}