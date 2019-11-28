#include "nn.h"

NN::NN()
{}

NN::NN(vector<int> structure) //just the structure
{
    NN_str=structure;
    weights.resize(structure.size()-1);
    for(int i=0; i<weights.size(); i++)//layers
    {
        weights[i].resize(structure[i]);
        for(int j=0; j<weights[i].size(); j++)//neurons
        {
            weights[i][j].resize(structure[i+1]);
            for(int k=0; k<weights[i][j].size(); k++)//sinapsis
            {
                weights[i][j][k]=((double)(rand()%1000))/1000.;
                wts.push_back(weights[i][j][k]);
            }
        }
    }
                
}

NN::NN(vector<int> structure, vector<vector<vector<double>>> w)  //structure and weights
{
    NN_str=structure;
    weights.resize(structure.size()-1);
    for(int i=0; i<weights.size(); i++)//layers
    {
        weights[i].resize(structure[i]);
        for(int j=0; j<weights[i].size(); j++)//neurons
        {
            weights[i][j].resize(structure[i+1]);
            for(int k=0; k<weights[i][j].size(); k++)//sinapsis
            {
                weights[i][j][k]=w[i][j][k];
                wts.push_back(weights[i][j][k]); 
            }
        }
    }
}
 

vector<double> NN::output(vector<double> input)
{
    double out;
    vector<vector<double>> value;
    value.resize(NN_str.size());
    //sizing the values holder
    for(int i=0; i<value.size(); i++)
    {
        value[i].resize(NN_str[i]);
    }
    //giving the input
    for(int i=0; i<input.size(); i++)
    {
        value[0][i]=input[i];
    }
    //calculating the output
    for(int i=0; i<value.size()-1; i++)//looping on layers
    {
        for(int j=0; j<value[i].size(); j++)//looping on neurons
        {
            for(int k=0; k<weights[i][j].size(); k++)//looping on weights of neuron
            {
                value[i+1][k]+=(weights[i][j][k])*(value[i][j]);
            }
        }
        for(int l=0; l<value[i+1].size(); l++)//using a transfer function
        {
            value[i+1][l]=identity(value[i+1][l]);
        }
    }
    int last_lay=NN_str.size()-1;
    for(int i=0; i<value[last_lay].size(); i++)//using the inverse of the transfer func
    {
        value[last_lay][i]=(value[last_lay][i]);
    }
    return value[last_lay];
}

double NN::error(string name, int nsample)
{
    fstream t_file(name);
    vector<vector<double>> inputs;
    vector<vector<double>> outputs;
    double mean_err=0;
    inputs.resize(nsample);
    outputs.resize(nsample);
    for(int i=0; i<inputs.size(); i++)
    {
        inputs[i].resize(NN_str[0]);
    }
    for(int i=0; i<outputs.size(); i++)
    {
        outputs[i].resize(NN_str[NN_str.size()-1]);
    }

    for(int i=0; i<nsample; i++)//reading the training file
    {
        for(int j=0; j<inputs[i].size(); j++)
        {
            t_file>>inputs[i][j];
        }
        for(int k=0; k<outputs[i].size(); k++)
        {
            t_file>>outputs[i][k];
        }
    }
    t_file.close();
    for(int i=0; i<nsample; i++)//calculating the mean_error
    {
        int a=rand()%nsample;
        for(int j=0; j<outputs[i].size(); j++)
        {
            mean_err+=sqrt((outputs[a][j]-output(inputs[a])[j])*(outputs[a][j]-output(inputs[a])[j]));
        }  
    }
    mean_err=mean_err/nsample;
    return mean_err;
}

void NN::w_set(vector<double> w)
{
    int count=0;
    for(int i=0; i<weights.size(); i++)
    {
        for(int j=0; j<weights[i].size(); j++)
        {
            for(int k=0; k<weights[i][j].size(); k++)
            {
                weights[i][j][k]=w[count];
                count++;
            }
        }
    }
}