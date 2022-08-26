#include "child.h"
#include <iostream>
#include <string>

using namespace std;

Child::Child()
{
    first_name_ = "";
    last_name_ = "";
    age_ = 0;
}

Child::Child(string first_name_, string last_name_, int age_)
{
    this->first_name_ = first_name_;
    this->last_name_ = last_name_;
    this->age_ = age_;
}

Child::~Child() {}


Child& Child::operator=(const Child& other)
{
    first_name_ = other.first_name_;
    last_name_ = other.last_name_;
    age_ = other.age_;
    return *this;
}



bool Child::operator>(const Child& other) const
{
    if (last_name_ == other.last_name_)
    {
        if (first_name_ > other.first_name_)
        {
            return true;
        }
        else if (first_name_ < other.first_name_)
        {
            return false;
        }
        else if (first_name_ == other.first_name_)
        {
            return age_ > other.age_;
        }
    }

    if (last_name_ > other.last_name_)
    {
        return true;
    }

    return false;
}


bool Child::operator<(const Child& other) const
{
    if (last_name_ == other.last_name_)
    {
        if (first_name_ < other.first_name_)
        {
            return true;
        }
        else if (first_name_ > other.first_name_)
        {
            return false;
        }
        else if (first_name_ == other.first_name_)
        {
            return age_ < other.age_;
        }
    }

    if (last_name_ < other.last_name_)
    {
        return true;
    }

    return false;
}


bool Child::operator>=(const Child& other)const
{
    if (last_name_ == other.last_name_)
    {
        if (first_name_ >= other.first_name_)
        {
            return true;
        }
        else if (first_name_ < other.first_name_)
        {
            return false;
        }
        else if (first_name_ == other.first_name_)
        {
            return age_ >= other.age_;
        }
    }

    if (last_name_ >= other.last_name_)
    {
        return true;
    }

    return false;
}


bool Child::operator<=(const Child& other) const
{
    if (last_name_ == other.last_name_)
    {
        if (first_name_ <= other.first_name_)
        {
            return true;
        }
        else if (first_name_ > other.first_name_)
        {
            return false;
        }
        else if (first_name_ == other.first_name_)
        {
            return age_ <= other.age_;
        }
    }

    if (last_name_ <= other.last_name_)
    {
        return true;
    }

    return false;
}


bool Child::operator==(const Child& other) const
{
    return (first_name_ == other.first_name_ && last_name_ == other.last_name_ && age_ == other.age_);
}


bool Child::operator!=(const Child& other) const
{
    return (first_name_ != other.first_name_ || last_name_ != other.last_name_ || age_ != other.age_);
}


ostream& operator<<(ostream& out_stream, const Child& other)
{
    out_stream << other.first_name_ << other.last_name_ << other.age_;
    return out_stream;
}