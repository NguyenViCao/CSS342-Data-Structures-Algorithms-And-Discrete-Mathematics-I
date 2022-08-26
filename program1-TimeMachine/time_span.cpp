#include "time_span.h"
#include <cmath>
#include <iostream>
using namespace std;

TimeSpan::TimeSpan() : hour_(0), minute_(0), second_(0)
{
}

TimeSpan::TimeSpan(double second) : hour_(0), minute_(0), second_(second)
{
	if (second > 60)
	{
		increase_seconds(round(second));
	}
	negative_time();
	total_seconds_ = round(second);
}

TimeSpan::TimeSpan(double minute, double second) : hour_(0), minute_(minute), second_(second)
{
	if (second > 60)
	{
		increase_seconds(round(second));
	}
	if (minute > 60)
	{
		increase_minutes(round(second));
	}
	negative_time();
	calculate_double();
	total_seconds_ = minute * 60 + round(second);
}

TimeSpan::TimeSpan(double hour, double minute, double second) : hour_(hour), minute_(minute), second_(second)
{
	if (second > 60 && minute > 60) 
	{
		increase_seconds(round(second));
	}
	else if (second > 60)
	{
		increase_seconds(round(second));
	}
	else if (minute > 60)
	{
		increase_minutes(minute);
	}
	negative_time();
	calculate_double();
	total_seconds_ = hour * 60 + minute * 60 + round(minute);
}

int TimeSpan::hours() const
{
	return hour_;
}

int TimeSpan::minutes() const
{
	return minute_;
}

int TimeSpan::seconds() const
{
	return second_;
}

void TimeSpan::set_time(int hours, int minutes, int seconds)
{
	hour_ = hours;
	minute_ = minutes;
	second_ = seconds;
}


TimeSpan TimeSpan::operator+(const TimeSpan& rhs) const
{
	TimeSpan a;
	int hours = hour_ + rhs.hours();
	int minutes = minute_ + rhs.minutes();
	int seconds = second_ + rhs.seconds();
	a.set_time(hours, minutes, seconds);
	if (seconds > 60 && minutes > 60)
	{
		a.increase_seconds(seconds);
	}
	else if (seconds > 60)
	{
		a.increase_seconds(seconds);
	}
	else if (minutes > 60)
	{
		a.increase_minutes(minutes);
	}
	a.negative_time();
	a.calculate_double();
	return a;
}

TimeSpan& TimeSpan::operator+=(const TimeSpan& rhs)
{
	int hours = hour_ + rhs.hours();
	int minutes = minute_ + rhs.minutes();
	int seconds = second_ + rhs.seconds();
	set_time(hours, minutes, seconds);
	if (seconds > 60 && minutes > 60)
	{
		increase_seconds(seconds);
	}
	else if (seconds > 60)
	{
		increase_seconds(seconds);
	}
	else if (minutes > 60)
	{
		increase_minutes(minutes);
	}
	negative_time();
	calculate_double();
	return *this;
}

TimeSpan TimeSpan::operator-(const TimeSpan& rhs) const
{
	TimeSpan a;
	int hours = hour_ - rhs.hours();
	int minutes = minute_ - rhs.minutes();
	int seconds = second_ - rhs.seconds();
	a.set_time(hours, minutes, seconds);
	if (seconds > 60 && minutes > 60)
	{
		a.increase_seconds(seconds);
	}
	else if (seconds > 60)
	{
		a.increase_seconds(seconds);
	}
	else if (minutes > 60)
	{
		a.increase_minutes(minutes);
	}
	a.negative_time();
	a.calculate_double();
	return a;
}

TimeSpan& TimeSpan::operator-=(const TimeSpan& rhs)
{
	int hours = hour_ - rhs.hours();
	int minutes = minute_ - rhs.minutes();
	int seconds = second_ - rhs.seconds();
	set_time(hours, minutes, seconds);
	if (seconds > 60 && minutes > 60)
	{
		increase_seconds(seconds);
	}
	else if (seconds > 60)
	{
		increase_seconds(seconds);
	}
	else if (minutes > 60)
	{
		increase_minutes(minutes);
	}
	negative_time();
	calculate_double();
	return *this;
}

TimeSpan TimeSpan::operator-()
{
	return TimeSpan(-hour_, -minute_, -second_);
}

bool TimeSpan::operator==(const TimeSpan& rhs) const
{
	return ((hour_ == rhs.hours()) && (minute_ == rhs.minutes()) && (second_ == rhs.seconds()));
}

bool TimeSpan::operator!=(const TimeSpan& rhs) const
{
	return !(*this == rhs);
}

bool TimeSpan::operator<(const TimeSpan& rhs) const
{
	return (this->total_seconds_ < rhs.total_seconds_);
}

bool TimeSpan::operator<=(const TimeSpan& rhs) const
{
	return (this->total_seconds_ <= rhs.total_seconds_);
}

bool TimeSpan::operator>(const TimeSpan& rhs) const
{
	return (this->total_seconds_ > rhs.total_seconds_);
}

bool TimeSpan::operator>=(const TimeSpan& rhs) const
{
	return (this->total_seconds_ >= rhs.total_seconds_);
}

void TimeSpan::increase_seconds(int current_seconds)
{
	// Not remain in second
	if (current_seconds % 60 == 0)
	{
		this->minute_ += current_seconds / 60;
		this->second_ = 0;
	}

	// Remain in second
	else 
	{
		this->minute_ += current_seconds / 60;
		this->second_ = 0;
		this->second_ += current_seconds % 60;
	}

	if (this->minute_ > 60) 
	{
		increase_minutes(this->minute_);
	}
}

void TimeSpan::increase_minutes(int current_minutes)
{
	// Not remain in second
	if (current_minutes % 60 == 0)
	{
		this->hour_ += current_minutes / 60;
		this->minute_ = 0;
		this->minute_ += current_minutes % 60;
	}

	// Remain in second
	else 
	{
		this->hour_ += current_minutes / 60;
		this->minute_ = 0;
		this->minute_ += current_minutes % 60;
	}
}

void TimeSpan::negative_time()
{
	while (second_ < 0)
	{
		if (minute_ <= 0 && hour_ > 0)
		{
			hour_--;
			minute_ += 60;
		}
		minute_--;
		second_ += 60;
	}
	while (minute_ < 0)
	{
		hour_--;
		minute_ += 60;
	}
	if (hour_ < 0)
	{
		second_ -= 60;
		minute_ = minute_ + 1 - 60;
		hour_++;
	}
	this->second_ = round(second_);
}


void TimeSpan::calculate_double()
{
	int no_decimal_hour_ = hour_;
	int no_decimal_minute_ = minute_;
	if (this->minute_ - no_decimal_minute_ != 0)
	{
		second_ += (minute_ - no_decimal_minute_) * 60;
	}
	if (this->hour_ - no_decimal_hour_ != 0)
	{
		minute_ += (hour_ - no_decimal_hour_) * 60;
	}
}

ostream& operator<<(ostream& stream, const TimeSpan& rhs)
{
	stream << "Hours: " << rhs.hours() << ",   Minutes: " << rhs.minutes() << ",  Seconds:" << rhs.seconds();
	return stream;
}

istream& operator>>(istream& stream, TimeSpan& rhs)
{
	stream >> rhs.hour_ >> rhs.minute_ >> rhs.second_;
	return stream;
}