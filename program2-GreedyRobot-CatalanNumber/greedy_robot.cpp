#include "robot.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

bool TotalPath(Robot& robot, TargetPoint& treasure, int shortest, int& paths, string s, int max, int count);
void FindNumPath(Robot& robot, TargetPoint& treasure, int shortest, int max);
void Movement(TargetPoint& copyRobot, TargetPoint& treasure, char ch, bool MoveDirection, int shortest, int& path, string s, int max, int count);

int main(int argc, char* argv[])
{
	if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL || argv[4] == NULL || argv[5] == NULL)
	{
		cout << "Please input 5 integer!" << endl;
	}
	else
	{
		if (argc > 6)
		{
			cout << "Only 5 integer please." << endl;
		}
		Robot robot(stoi(argv[1]), stoi(argv[2]));
		TargetPoint treasure(stoi(argv[3]), stoi(argv[4]));
		int max_step = stoi(argv[5]);

		int shortest_distance = robot.CalculateDistance(treasure);

		FindNumPath(robot, treasure, shortest_distance, max_step);
	}
}

bool TotalPath(Robot& robot, TargetPoint& treasure, int shortest, int& paths, string s, int max, int count)
{
	if (robot.CalculateDistance(treasure) == 0 && shortest == 0 && count <= max)
	{
		//robot is right at treasure point
		if (paths == 0 && s == "")
		{
			return true;
		}
		else
		{
			cout << s << endl;
			paths++;
			return true;
		}
	}
	else
	{
		TargetPoint copyRobot = robot.get_point();
		Movement(copyRobot, treasure, 'N', copyRobot.MoveNorth(), shortest, paths, s, max, count);

		copyRobot = robot.get_point();
		Movement(copyRobot, treasure, 'S', copyRobot.MoveSouth(), shortest, paths, s, max, count);

		copyRobot = robot.get_point();
		Movement(copyRobot, treasure, 'E', copyRobot.MoveEast(), shortest, paths, s, max, count);

		copyRobot = robot.get_point();
		Movement(copyRobot, treasure, 'W', copyRobot.MoveWest(), shortest, paths, s, max, count);
	}
	return true;
}

void Movement(TargetPoint& copyRobot, TargetPoint& treasure, char ch, bool MoveDirection, int shortest, int& path, string s, int max, int count)
{
	if (MoveDirection && copyRobot.CalculateDistance(treasure) < shortest && count <= max)
	{
		Robot tempRobot(copyRobot.get_x(), copyRobot.get_y());
		int n = count;

		//compare character ch with the previous character in s string and increment if they are the same
		if (s.size() > 0 && s.at(s.size() - 1) == ch)
		{
			n++;
		}
		else
		{
			n = 1;
		}
		TotalPath(tempRobot, treasure, shortest - 1, path, s + ch, max, n);
	}
}

void FindNumPath(Robot& robot, TargetPoint& treasure, int shortest, int max)
{
    int count = 1;
    int path = 0;
    string s = "";
    TotalPath(robot, treasure, shortest, path, s, max, count);
    cout << "Number of path: " << path << endl;
}