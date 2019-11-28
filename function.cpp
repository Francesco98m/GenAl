#include<iostream>
#include<vector>
#include<math.h>
#include<fstream>
#include<set>
#include<chrono>
#include<tuple>
#include<algorithm>

using namespace std;

double identity(double in)
{
    return in;
}

double ReLU(double in)
{
    if(in<=0) return 0;
    else return in;
}

double sigmoid(double in)
{
    return (1./(1.+exp(-in)));
}

double asigmoid(double in)
{
    return (log(1.-(1./in)));
}

double tgh(double in)
{
    return tanh(in);
}

double atgh(double in)
{
    return atanh(in);
}