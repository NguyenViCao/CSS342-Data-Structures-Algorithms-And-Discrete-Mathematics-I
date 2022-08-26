#include <iostream>
#include <string>
using namespace std;

int Catalan(int a);

int main(int argc, char* argv[])
{
    if (argv[1] == NULL)
    {
        cout << "Please input a number!" << endl;
    }
    else
    {
        if (argc > 2)
        {
            cout << "Only 1st number count." << endl;
        }

        int number = stoi(argv[1]);
        cout << Catalan(number) << endl;
    }
    return 0;
}

int Catalan(int a)
{
    int c = 0;
    if (a < 0)
        return -1;
    if (a == 0)
        return 1;
    for (int i = 0; i < a; i++)
    {
        c = c + Catalan(i) * Catalan(a - i - 1);
    }
    return c;
}
