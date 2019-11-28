#include "nn.cpp"

//create a population of pop net, then select the top 15 and return those
vector<NN> selection(vector<NN> sample,string name, int nsample, int nets)
{
    vector<NN> selection;
    //set<double> errors;
    vector<tuple<double,int>> errors;
    int counter=0;
    //set<double>::iterator it;
    double err;
    for(int i=0; i<sample.size(); i++)
    {
        err=sample[i].error(name,nsample);
        sample[i].err=err;
        errors.push_back(make_tuple(err,i));
    }
    sort(errors.begin(),errors.end());
    for(int i=0; i<nets; i++)
    {
        selection.push_back(sample[get<1>(errors[i])]);
    }
    /*while(counter<nets)
    {
        it=errors.begin();
        //cout<<errors.size()<<endl;
        for(int j=0; j<sample.size(); j++)
        {
            if(sample[j].err==*it)
            {
                selection.push_back(sample[j]);
                errors.erase(it);
            }
        }
        counter++;
    }*/
    //cout<<"SELECTION DONE\n";
    return selection;

}

//receive the selected net from selection, then they get crossed and it is created a new population
vector<NN> generation(vector<NN> selected)
{
    if(selected.size()==1) return selected;
    vector<NN> new_batch;
    vector<double> new_weights;
    vector<int> str=selected[0].NN_str;
    int dna=selected[0].wts.size();
    int count=0,count2=0;;
    int a=0,b=0,c=0;
    int a1,b1,c1;
    for(int i=0; i<selected.size(); i++)
    {
        for(int j=0; j<selected.size(); j++)
        {
            if(j!=i)
            {
                //--------------first net dna--------------//
                //cout<<"BEFORE DNA #1\n";
                while(a<selected[i].weights.size())//layer
                {
                    while(b<selected[i].weights[a].size())//neuron
                    {
                        while(c<selected[i].weights[a][b].size())//synapsis
                        {
                            new_weights.push_back(selected[i].wts[count]);
                            count++;
                            if(count>(dna/2))
                            {
                                a1=a;
                                b1=b;
                                c1=c;
                                break;
                            }
                            c++;
                        }
                        if(count>(dna/2)) break;
                        c=0;
                        b++;
                    }
                    if(count>(dna/2)) break;
                    b=0;
                    a++;
                }
                //--------------second net dna-------------//
                a=a1;
                b=b1;
                c=c1;
                //cout<<"BEFORE DNA #2\n";
                while(count<dna)
                {
                    while(a<selected[j].weights.size())//layer
                    {
                        while(b<selected[j].weights[a].size())//neuron
                        {
                            while(c<selected[j].weights[a][b].size())//synapsis
                            {
                                new_weights.push_back(selected[j].wts[count]);
                                count++;
                                c++;
                            }
                            c=0;
                            b++;
                        }
                        b=0;
                        a++;
                    }
                }
                new_batch.push_back(NN(str));
                new_batch[count2].w_set(new_weights);
                count2++;
                //cout<<"DNA DONE\t"<<count2<<endl;
            }
        }
    }
    //it created i*j-j new net so the j missing can be done with the mutations
    vector<double> piero;
    for(int i=0; i<selected.size(); i++)
    {
        piero=selected[i].wts;
        new_batch.push_back(NN(str));
        int a=rand()%(selected[i].wts.size());
        for(int j=0; j<a; j++)
        {
            double mutat=((double)(rand()%5)/100.);
            int sign=rand()%100;
            if(sign<50) piero[j]=selected[i].wts[j]+mutat;
            else piero[j]=selected[i].wts[j]-mutat;
        }
        new_batch[new_batch.size()-1].w_set(piero);
    }
    //cout<<"GENERATION DONE\n";
    //cout<<"Size of the new batch: "<<new_batch.size()<<endl;
    return new_batch;
}

vector<NN> training(int epoch, vector<NN> app1, string name, int nsample, string graph, int nets)
{
    int counter=0;
    vector<NN> app2;
    double err;
    graph.append(".txt");
    ofstream o(graph);
    while(counter<epoch)
    {
        app2=selection(app1,name,nsample,nets);
        err=app2[0].error(name,nsample);
        app1=generation(app2);
        o<<counter;
        o<<'\t';
        o<<err;
        o<<'\n';
        counter++;
        if(counter%100==0) cout<<"Done "<<counter<<" selection\n";
        
    }
    o.close();
    return selection(app1,name,nsample,nets);
}

