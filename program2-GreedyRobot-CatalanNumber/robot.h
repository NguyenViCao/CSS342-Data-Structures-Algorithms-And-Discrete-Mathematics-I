#ifndef ROBOT_H_
#define ROBOT_H_
#include <iostream>
#include "target_point.h"
using namespace std;

class Robot : public TargetPoint
{
public:
	//constructor
	Robot();
	Robot(int x1_, int y1_);

	//getters-setters
	int distance();
	void set_distance(int d);

	//verb - action
	Robot& MoveNorth();
	Robot& MoveEast();
	Robot& MoveWest();
	Robot& MoveSouth();

	//operator overloading
	Robot& operator=(Robot& robot2);

private:
	int x1_;			//x coordinate of the robot
	int y1_;			//y coordinate of the robot
	int distance_;
};
#endif