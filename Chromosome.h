#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include<math.h>
#include <bits/stdc++.h>
#include<time.h>
#include<iostream>
#include<iterator>
#include<algorithm>
#include<omp.h>


#define num popnum  //num of numbers in the vector
#define factor 0.6 //factor for the fit_function
#define pins (num*num/2-num/2)
#define min_cut_percent mincutper
using namespace std;

class Chromosome
{
public:
  
    //Constructor_empty Chromosome
    Chromosome();
    //Constructor_chromosome
    Chromosome(int,short int[num],int,int,int);//
    //Destructor
    ~Chromosome();

    //Variables
    int length;
  short   int chromosome_array[num];
    int partitions;
    int geneid;
    int id;

    //functions

//returns the cost of the chromo
    double fit_function(short int arr[num],short int con[pins])
    {
        int sums[partitions]= {0};
        int c=0;
        double f=0;

#pragma omp parallel for collapse(2)  reduction(+:sums) //num_threads(16)
        for(int i=0; i<length; i++)
        {
            for(int j=0; j<partitions; j++)
            {
                if(chromosome_array[i]==j)
                {
                    sums[j]+=arr[i];
                }
            }

        }



        #pragma omp parallel for   reduction(+:c) //num_threads(16)
       for(int i=0; i<length; i++)
        {

            c+=arr[i];
        }


        double c1=c/partitions;

        #pragma omp parallel for   reduction(+:f) //num_threads(16)
        for(int i=0; i<partitions; i++)
        {


            f+=abs(sums[i]-c1);
        }


        double min_cut=0;

        #pragma omp parallel for collapse(2)  reduction(+:min_cut) //num_threads(16)
        for(int i=1;i<num;i++){

            for(int j=0;j<num;j++){

                if(j<i) {
               min_cut+=con[(i*i/2-i/2)+j]*abs(chromosome_array[i]-chromosome_array[j]);
                }
}
}

int pinsum=0;
 #pragma omp parallel for   reduction(+:pinsum) //num_threads(16)
      for(int i=0;i<pins;i++){
        pinsum+=con[i];

        }


pinsum*=min_cut_percent;

double fin_fit_fun=0;


fin_fit_fun=factor*f/c1 + (1-factor)*(min_cut-pinsum)/pinsum ;

        return fin_fit_fun;
    }

// getmincut returns the min_cut of the chromosome
   int getmincut(short int arr[num],short int con[pins]){

    int  min_cut=0;

    #pragma omp parallel for collapse(2)  reduction(+:min_cut) //num_threads(16)
        for(int i=1;i<num;i++){

            for(int j=0;j<num;j++){

                if(j<i) {
               min_cut+=con[(i*i/2-i/2)+j]*abs(chromosome_array[i]-chromosome_array[j]);
                }
}
}
return min_cut;
}


//getsum returns the mean of abs(sum(i)-sum)
double getsum(short int arr[num],short int con[pins]){



 int sums[partitions]= {0};
        int c=0;
        double f=0;
      #pragma omp parallel for collapse(2)  reduction(+:sums) //num_threads(16)
        for(int i=0; i<length; i++)
        {
            for(int j=0; j<partitions; j++)
            {
                if(chromosome_array[i]==j)
                {
                    sums[j]+=arr[i];
                }
            }

        }
      #pragma omp parallel for   reduction(+:c) //num_threads(16)
       for(int i=0; i<length; i++)
        {

            c+=arr[i];
        }


        double c1=c/partitions;

         #pragma omp parallel for   reduction(+:f) //num_threads(16)
        for(int i=0; i<partitions; i++)
        {


            f+=abs(sums[i]-c1);
        }


return f;

}







    //prints the chromosome
    void chromoprint()
    {
        cout<<"Chromo_"<<id<<"_"<<geneid<<"=[ ";
        for(int i=0; i<num; i++)
        {
            cout<<chromosome_array[i]<<"  ";
        }
        cout<<" ]"<<endl;
    }

    //prints the chromosome
    void chromoprint_final()
    {
        cout<<"-> Partition"<<"=[ ";
        for(int i=0; i<num; i++)
        {
            cout<<chromosome_array[i]<<" ";
        }
        cout<<" ] <-";
    }

};

#endif // CHROMOSOME_H
