#include "Chromosome.h"

#include <random>
#include <iostream>
#include <vector>
using namespace std;




//empty constructor
Chromosome::Chromosome()
{
    length=0;
    id=0;
    geneid=0;
    for(int i=0; i<num; i++)
    {
        chromosome_array[i]=0;
    }

}


//constructor with  values
Chromosome::Chromosome(int lengthof, short int chromosome_arrayof[num],int p,int gid,int cid)
{
    length=lengthof;


    for(int i=0; i<num; i++)
    {
        chromosome_array[i]=chromosome_arrayof[i];
    }



    partitions=p;
    geneid=gid;
    id=cid;

}



//Destructor
Chromosome::~Chromosome()
{
    // cout<<"element type Chromosome id_geneid: "<<id<<"_"<<geneid<<" destructed"<<endl;
}
