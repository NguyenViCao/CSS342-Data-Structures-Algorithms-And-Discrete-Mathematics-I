#include "time_span.h"
#include <iostream>
using namespace std;

int main()
{
    TimeSpan dur1(77.4, 15, 6), dur2(127.86), dur3(8, -23, 0), dur4(0, 0, 0);
    TimeSpan dur5(-3, 73, 2), dur6(7, 35, 120), dur7, dur8;
    
    dur7 = dur1 + dur3;

    cout << dur1 << endl;
    cout << dur2 << endl;
    cout << dur3 << endl;
    cout << dur4 << endl;
    cout << dur5 << endl;
    cout << dur6 << endl;
    cout << dur7 << endl;

    dur7 += dur3;
    cout << dur3 << endl;
    cout << dur7 << endl;

    if (dur3 != dur6) 
    { 
        cout << "Durations are different." << endl; 
    }
    else
    {
        cout << "Durations are the same" << endl;
    }
}

