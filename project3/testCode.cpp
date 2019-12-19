#include <iostream>
#include <stdio.h>
using namespace::std;

int fact(int n)
{
    if (n == 1)
        return n;
    else
        return (n * fact(n-1));
}
int main()
{
    int m, result;
    m = 10;
    if (m > 1)
        result = fact(m);
    else
        result = 1;
    cout<<result<<endl;
    return 0;
}
