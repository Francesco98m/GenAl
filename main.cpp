#include "genetic.cpp"

int main()
{
    srand(time(NULL));
    vector<int> NN_str;
    vector<double> input;
    vector<double> output;
    vector<NN> app1,batch;
    NN neo;
    string name;
    int samples;
    int nets,epoch;
    int selec=0,a=0, counter=0;
    bool esc=true,start=true;
    while(esc)
    {
        if(start)
        {
            cout<<"Choose a structure for the net: \nLayers= ";
            cin>>a;
            NN_str.resize(a);
            for(int i=0; i<NN_str.size(); i++)
            {
                cout<<"Number of neurons in the layer "<<i<<" : ";
                cin>>NN_str[i];
                cout<<endl;
            }
            input.resize(NN_str[0]);
            output.resize(NN_str[NN_str.size()-1]);
            neo=NN(NN_str);
            cout<<"Net created\n";
            start=false;
        }
        cout<<"Choose what to do:\n";
        cout<<"[0]-Give input\n[1]-Get mean error\n[2]-Train with genetic algorithm\n[3]-Exit\n";
        cin>>selec;
        if(selec==0)//input
        {
            cout<<"Insert input:\n";
            for(int i=0; i<input.size(); i++)
            {
                cin>>input[i];
            }
            output=neo.output(input);
            cout<<"The result is: \t";
            for(int i=0; i<output.size(); i++)
            {
                
                cout<<output[i]<<endl;
            }  
        }
        else if(selec==1)//mean error
        {
            cout<<"Name of the file:\t";
            cin>>name;
            cout<<"Number of sample:\t";
            cin>>samples;
            cout<<"The mean error is: ";
            cout<<neo.error(name,samples)<<endl;
        }
        else if(selec==2)//genetic
        {
            cout<<"How many nets do you want to select?(more than 10 less than 100)\t";
            cin>>nets;
            cout<<"How many selections?\t";
            cin>>epoch;
            for(int i=0; i<100; i++)
            {
                app1.push_back(NN(NN_str));
            }
            cout<<"Nets created\n";
            cout<<"Now the natural selection begin...\n";
            auto start=chrono::high_resolution_clock::now();

            batch=training(epoch,app1,"test_p",100,"identity",nets);
            
            auto finish =chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed=finish-start;
            cout<<"Total elapsed time:\t"<<elapsed.count()<<" sec.\n";
            neo=batch[0];
            cout<<"Now we have the best net generated saved\n";
        }
        else if(selec==3)
        {
            esc=false;
        }
    }
    
}