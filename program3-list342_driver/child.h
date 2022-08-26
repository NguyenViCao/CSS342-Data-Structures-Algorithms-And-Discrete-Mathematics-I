#ifndef CHILD_H_
#define CHILD_H_
#include <string>
#include <iostream>
using namespace std;

class Child
{
public:
    Child();
    Child(string first_name_, string last_name_, int age_);
    ~Child();


    Child& operator=(const Child& other);
    bool operator>(const Child& other) const;
    bool operator<(const Child& other) const;
    bool operator<=(const Child& other) const;
    bool operator>=(const Child& other) const;
    bool operator==(const Child& other) const;
    bool operator!=(const Child& other) const;

    friend ostream& operator<<(ostream& out_stream, const Child& other);

private:
    string first_name_;
    string last_name_;
    int age_;
};
#endif