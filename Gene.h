#ifndef GENE_H
#define GENE_H

#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<iostream>
#include <time.h>
#include "Chromosome.h"
#include <bits/stdc++.h>
#include<algorithm>
#include<iterator>
using namespace std;
#include <omp.h>

//#define par 4//num of partitions
#define numofc 25//number of Chromosomes in a Gene
#define swaps 2*numofc //number of swaps for the mix

class Gene : public Chromosome
{
    //Constructors and Destructor
public:
    //int par;
    Gene();
    Gene(int,int,double);
    Gene(int,int,double,vector<Chromosome>);
    ~Gene();

int par; 
// Variables
    vector<Chromosome>  chromoVector;//Vector of chromos
    vector<Chromosome> newGen;//vector of mixed chromos for input to next gene
    int idg;//id of gene
    int numofchromos;//num of chromos of the gene
    double threshold;//threshold for mix (~85-95%)
    int bestid;   //only after running best chromo_function


//given parent creates first generation inserts random numbers from 0 to par to each chromo_array of the gene
    void createFirstgene()
    {
        time_t t;
        srand(time(&t));


        for(int i=0; i<numofchromos; i++)
        {
           short  int a[num]= {0};

            for(int j=0; j<num; j++)
            {
                a[j]=rand()%par;
            }

            Chromosome c(num,a,par,1,i);
            chromoVector.push_back(c);
        }
    }

//prints a gene
    void geneprint()
    {
        cout<<endl;
        cout<<"_______________Generation_"<<idg<<"__________________"<<endl;
        for(unsigned int i=0; i<chromoVector.size(); i++)
        {

            chromoVector[i].chromoprint();
        }
       cout<<"_______________________________________________"<<endl;
    }


//finds the chromo whith the best fit_function of the gene and prints the fit_function and the chromo_id
    double bestchromo(short int parent[num],short int conect[pins])
    {

        int best_id=0;
        double bestg=chromoVector[0].fit_function(parent,conect);


        for(int i=0; i<numofc; i++)
        {
            if(chromoVector[i].fit_function(parent,conect)<bestg)
            {
                bestg=chromoVector[i].fit_function(parent,conect);
                best_id=chromoVector[i].id;
            }
        }
        bestid=best_id;

       // cout<<endl<<"best partition of  gene "<<idg<<" fit_fun = "<<bestg<<" owned by chromo :"<< best_id <<endl;



        return bestg;

    }





    double bestchromo_n(short int parent[num],short int conect[pins])
    {

        //int best_id=0;
        double bestg=chromoVector[0].fit_function(parent,conect);


        for(int i=0; i<numofc; i++)
        {
            if(chromoVector[i].fit_function(parent,conect)<bestg)
            {
                bestg=chromoVector[i].fit_function(parent,conect);
               // best_id=chromoVector[i].id;
            }
        }
        //bestid=best_id;





        return bestg;

    }


     void numberswapchrom(short int *a,short int *b)
    {
        int pivot=*a;

        *a=*b;
        *b=pivot;
    }

//Not used !!!
double getmean_f(int current_id,short int arr[num],short int con[pins]){
    double mean_f=0;

    for(int k=0;k<current_id;k++){

    mean_f+=chromoVector[k].getsum(arr,con);

    }
    mean_f=mean_f/current_id;

    return mean_f;
    }

//Not used !!!
//returns the mean mincut of gene from start to current_id chromosome
    double getmean_mincut(int current_id,short int arr[num],short int con[pins]){
    double mean_mincut=0;

    for(int k=0;k<current_id;k++){

    mean_mincut+=chromoVector[k].getmincut(arr,con);

    }
    mean_mincut=mean_mincut/current_id;

    return mean_mincut;
    }


    //mix chromo's function
    //given two chromosomes mixes them and creates two new chromo's with geneid++
    void mix(int id1,int id2,int crossover)
    {


//function swaps two numbers
        #pragma omp parallel for
        for(int i=0; i<crossover; i++)
        {
            numberswapchrom(&chromoVector[id1].chromosome_array[i],&chromoVector[id2].chromosome_array[i]);
        }

       // cout<<"mix of chromo_"<<chromoVector[id1].id<<"_"<<chromoVector[id1].geneid<<" and chromo_"<<chromoVector[id2].id<<"_"<<chromoVector[id2].geneid<<" at point "<<crossover<<endl;
       // cout<<endl;

    }


    //creates new generation
    void createGene(short int parent[num],short int conect[pins])
    {  // cout<<endl<<"____________________Mix_______________________"<<endl;

      time_t t2;
        int parent1=0;
        int parent2=0;
        int parents[swaps]= {};
        //for every swap chose randomly two parents and keep the best of them for the mixes
        #pragma omp parallel
        {
         srand(int(time(&t2)) >>( omp_get_thread_num()));
          #pragma omp for private(parent1,parent2)
        for(int i=0; i<swaps; i++)
        {
            parent1=(int)rand()%chromoVector.size();

            parent2=(int)rand()%chromoVector.size();

            parents[i]=parent2;
            if(chromoVector[parent1].fit_function(parent,conect)>chromoVector[parent2].fit_function(parent,conect))
            {
                parents[i]=parent1;
            }
           /* else
           {
               parents[i]=parent2;
           }*/
        }
        }
        //cout<<endl;


        std::random_shuffle(std::begin(parents),std::end(parents));//blend the array with the chromosomes for mix
     /*   cout<<"Parents(pairs per two) : ";
        for(int k=0;k<swaps;k++){
         if(k%2==0){
        cout<<"<"<<parents[k]<<" ";}
        else{
           cout<<parents[k]<<">"<<"..";
        }
        }cout<<endl<<endl;*/

      //  every two chromosomes from the selected create a random number from 0 to 1 and if this is under 85% do the mix


      float prob=0;
      int crossover=0;

     //float probarray[numofc]={-1};
      //int crosspoint_array[numofc]={-1};
        time_t t3;
        #pragma omp parallel
        {
         srand(int(time(&t3)) >>( omp_get_thread_num()+geneid*geneid));
        // #pragma omp paralle for private(prob,crossover)
        for(int i=0; i<numofc; i++)
        {
           // prob=((float)rand()/RAND_MAX);
           prob=rand()%1000;
           prob/=1000;
           // probarray[i]=prob;
          // cout<<i/2<<"____";
          // cout<<prob<<endl;
            if(prob<threshold)
            {   //cout<<"ok"<<endl;
                crossover=rand()%num;
               //crosspoint_array[i]=crossover;
                mix(parents[2*i],parents[2*i+1],crossover);
            }
            /*else
            {
                cout<<"-----over 85%-----"<<endl;
                cout<<endl;
            }*/
        }

        }
//cout<<"Treshold : "<<threshold<<endl;
/*cout<<"Probs : ";
for(int k=0;k<numofc;k++){
        if(probarray[k]>threshold)
        {cout<<"--<"<<probarray[k]<<">--"<<" ";}
       else
        cout<<probarray[k]<<" ";
        }
        cout<<endl<<endl;
//cout<<"Number of elements : "<<num<<endl;
cout<<"CrossOvers : ";
for(int k=0;k<numofc;k++){cout<<crosspoint_array[k]<<" ";}cout<<endl;*/

        for(unsigned int i=0; i<chromoVector.size(); i++)
        {

            Chromosome cnew(num,chromoVector[i].chromosome_array,par,idg+1,i);

            newGen.push_back(cnew);
        }



    }



};

#endif // GENE_H
