#include "function.cpp"

class NN
{
    public:
    //-----------costrunctor-------------//
    NN();
    NN(vector<int>);
    NN(vector<int>, vector<vector<vector<double>>>);

    //-----------method-----------------//
    vector<double> output(vector<double>);
    double error(string, int);
    void w_set(vector<double>);

    //-----------variables--------------//
    vector<int> NN_str;
    vector<double> wts;
    vector<vector<vector<double>>> weights;
    double err;

};