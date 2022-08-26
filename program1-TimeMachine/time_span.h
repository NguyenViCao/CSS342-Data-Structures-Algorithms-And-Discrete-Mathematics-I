#ifndef TIMESPAN_H_
#define	TIMESPAN_H_
#include <iostream>
using namespace std;
class TimeSpan
{
public:
	//constructor
	TimeSpan();
	TimeSpan(double second_);
	TimeSpan(double minute_, double second_);
	TimeSpan(double hour_, double minute_, double second_);

	//getters-setters
	int hours() const;
	int minutes() const;
	int seconds() const;
	void set_time(int hours, int minutes, int seconds);

	//Method
	TimeSpan operator+(const TimeSpan& rhs) const;
	TimeSpan& operator+=(const TimeSpan& rhs);
	TimeSpan operator-(const TimeSpan& rhs) const;
	TimeSpan& operator-=(const TimeSpan& rhs);
	
	//unary negation
	TimeSpan operator-();

	bool operator==(const TimeSpan& rhs) const;
	bool operator!=(const TimeSpan& rhs) const;
	bool operator<(const TimeSpan& rhs) const;
	bool operator<=(const TimeSpan& rhs) const;
	bool operator>(const TimeSpan& rhs) const;
	bool operator>=(const TimeSpan& rhs) const;

														
	friend ostream& operator<<(ostream& stream, const TimeSpan& rhs);
	friend istream& operator>>(istream& stream, TimeSpan& rhs);

private:
	double hour_;
	double minute_;
	double second_;
	double total_seconds_;
	void increase_seconds(int current_seconds_);
	void increase_minutes(const int current_minutes_);
	void negative_time();
	void calculate_double();
};
#endif