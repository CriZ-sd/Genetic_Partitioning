#include <iostream>
#include "Chromosome.h"
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Gene.h"
#include<algorithm>
#include<fstream>
#include<string>
#include<sys/time.h>
#include <unistd.h>

#define maxer 100
#define bestlifetime 500
#define numofgenes 9999  // num of genes
#define stde  0//0.175 //best solution -> fitfun =0 / stops the exe when fitfun=stde
#define thres 0.65 //threshold of the genes for the mix
#define lifetime thelifetime //max number of rounds to stop if not getting better
#define gbetter  thegbetter//0.00065 //percentage of improvement in every gene

using namespace std;

void testfun(short int arr1[num],short int arr2[num],double m,short int arr3[pins],int partition_num)
{
    cout<<endl<<endl<<endl<<"*******************************************"<<endl;
    cout<<endl<<"____Testing_the_quality_of_the_solution____"<<endl;
    cout<<"best = mean = "<<m<<endl;
    /*cout<<"Sol_under_test =[";
    for(int j=0; j<num; j++)
    {
        cout<<" "<<arr1[j];
    }
    cout<<" ]"<<endl;
*/
   int sum[partition_num]= {};
 #pragma omp parallel for collapse(2)  reduction(+:sum)
    for(int k=0; k<num; k++)
    {

        for(int l=0; l<partition_num; l++)
        {
            if(arr1[k]==l)
            {
                sum[l]+=arr2[k];
            }
        }
    }

    for(int j=0; j<partition_num; j++)
    {
        cout<<"sum_of_par_"<<j<<" : "<<sum[j]<<" dist_from_best : "<<sum[j]-m<<endl;

    }

double sumall=0;
#pragma omp parallel for   reduction(+:sumall)
for(int k=0;k<partition_num;k++){

    sumall+=abs(sum[k]-m);

}
    int mincut=0;
  #pragma omp parallel for collapse(2) reduction(+:mincut)
    for(int k=1;k<num;k++){
        for(int l=0;l<num;l++){
            if(l<k ){
            mincut+=arr3[(k*k/2-k/2)+l]*abs(arr1[k] != arr1[l]);
            }
        }

    }



    cout<<endl<<"Min_Cut : "<<mincut<<endl;

    cout<<endl<<"f : "<< sumall<<endl;

    cout<<endl<<"*******************************************"<<endl;



}


int nonezero(short int myarr[pins]){

int counter=0;

#pragma omp parallel for  reduction(+:counter)
for(int k=0;k<pins;k++){



        if( myarr[k] > 0)
            {
            counter++;        }

}

return counter;
}



int main(int argc,char** argv)
{

    /*->*/ //double ff[numofgenes]={0};
    //int min__cut[numofgenes]={0};
//double sumquality[numofgenes]={0};
    //input array
  short int arraynew[num];
  short int con_array[pins];
    //Start Menu
   // int select=0;
    


    time_t t1;

    srand(time(&t1));


    

        string filename=(argv[1]);
        ifstream inputfile;
        int c=0;

       // cout<<"Nodes: Insert (carefully!) the file name...('name.txt')"<<endl;
        //cin>>filename;
        cout<<endl;
        inputfile.open(filename);
        int i_1=0;
        while(i_1<num && inputfile >> c)
        {
            arraynew[i_1]=c;
            i_1++;
        }
        inputfile.close();

        /*cout<<"array=[ ";

        for(int i=0; i<num; i++)
        {
            cout<<arraynew[i]<<" ";
        }
        cout<<" ]"<<endl;*/

        string filename_b=(argv[2]);
    ifstream inputfile_b;
    int d=0;

   //cout<<endl<<"Edges : Insert (carefully!) the file name   ...('name.txt')"<<endl;
     //  cin>>filename_b;
        cout<<endl;
        inputfile_b.open(filename_b);
    int q=0;
    while (q<pins && inputfile_b >> d){


        con_array[q]=d;
        q++;
        }
    inputfile_b.close();



    /*cout<<endl<<"Intercon=[ ";

    for(int j=1;j<10;j++){
        cout<<endl;
        for(int k=0;k<j;k++){

            cout<<setw(3)<<con_array[(j*j/2-j/2)+k];
            cout<<"("<<j<<","<<k<<") ";
        }
        }
        if(num<=10){
    cout<<"]"<<endl;
        }
        else{cout<<endl;

        for(int m=0;m<80;m++){

            cout<<".";
            }
            cout<<"]"<<endl;
            }
*/



    //compute the mean of the sums
    double mo=0;
   // #pragma omp parallel for   reduction(+:mo)
    for(int i=0; i<num; i++)
    {
        mo+=arraynew[i];
    }

     


    cout<<endl;
   // cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<"Number of Partitions : "<<par<<endl<<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    //cout<<endl<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;
    //cout<<"Number of Genes : "<<(numofgenes+1)<<" | Fit_fun Bound : "<<stde<<"| percentage_of_improvement: "<<gbetter<<" | lifetime: "<<lifetime<<" | " <<"Factor : " <<factor<<endl;
    //cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;


   // int NumofIntercons=0;
   //NumofIntercons=nonezero(con_array);



    double pinsum=0;
   for(int k=0;k<pins;k++){

    pinsum+=con_array[k];
    }


   pinsum*=min_cut_percent;
   //cout<<"***sum_of_node_weights = "<<mo<<" ***"<<endl;
   
   //cout<<"***mean_of_node_weights = "<<mo<<" ***"<<endl;
   //cout<<endl<<"*** NumOfIntercons = "<<NumofIntercons<<" ***"<<endl;
   //cout<<endl<<"***Sum_of_intercon_weights  : "<<pinsum/min_cut_percent<<" ***"<<endl;
   //cout<<"***Target_for_mincut (Sum_of_intercon_weights x "<<min_cut_percent<<" ) : "<<pinsum<<" ***"<<endl;

   

   cout<<endl<<"==> Starting..."<<endl;


    timeval tim;
    gettimeofday(&tim,NULL);
    double time1 = tim.tv_sec;

    //create First gene
    Gene Firstgene(1,numofc,thres); //create a gene with gid=1 ,number of chromo=numofc,threshold=0.85
   Firstgene.par=atoi(argv[5]);
    Firstgene.createFirstgene(); //fill up the chromo_arrays of the chromo's of first gene
    mo/=Firstgene.par;
  //  Firstgene.geneprint(); //print first gene



    double f_best=Firstgene.bestchromo(arraynew,con_array); //print best chromo of first gene
    double all_best=f_best;
    int    best_g=1;
    int    best_c=Firstgene.bestid;
   /*->*/
           /*ff[0]=f_best;
           min__cut[0]=Firstgene.chromoVector[Firstgene.bestid].getmincut(arraynew,con_array);
           sumquality[0]=Firstgene.chromoVector[Firstgene.bestid].getsum(arraynew,con_array);
               */


//create a gene vector with all the new genes
    vector <Gene> Mygenes;

    Mygenes.push_back(Firstgene); //first element of vector is Firstgene
       // cout<<endl<<"balanced_par=(f-mean)/mean_gene_"<<1<<" x factor ( "<<factor<<" ) : "<<(Firstgene.chromoVector[Firstgene.bestid].getsum(arraynew,con_array)/mo)*factor<<endl;
        //cout<<"mincut=(m-pinsum)/pinsum_gene_"<<1<<" x (1-factor) ( "<<1-factor<<" ) : "<<((Firstgene.chromoVector[Firstgene.bestid].getmincut(arraynew,con_array)-pinsum)/pinsum)*(1-factor)<<endl;
      /*  cout<<"Pinsum (sum_of_intercon x"<<min_cut_percent<<") :"<<pinsum<<endl;
        cout<<"Factor : "<<factor<<endl;
        cout<<"f_f=factor x balanced_par + (1-factor) x min_cut"<<endl;*/
//testfun(Mygenes[0].chromoVector[Firstgene.bestid].chromosome_array,arraynew,mo,con_array);

   short  int finalsol[num]= {};
    double last=0;
   // double tlast=0;
    int i=0;
    double best=f_best;
    double better=0;
    int lifet=0;
    int lifefrombest=bestlifetime;

    srand(time(&t1));

    //create new genes for the vector for max=numofgene until best_fit_function <= stde

    while(i<numofgenes && lifet<lifetime && best>stde && lifefrombest>0)
    {
       /* if(lifet == 0)
        {
            tlast=Mygenes[i].bestchromo_n(arraynew,con_array);
        }*/
        last=Mygenes[i].bestchromo_n(arraynew,con_array);
        Mygenes[i].createGene(arraynew,con_array); //create the new chromo_vector for next gene
        Gene Newgene(i+2,numofc,thres,Mygenes[i].newGen); //create the new gene
        Newgene.par=atoi(argv[5]);
        Mygenes.push_back(Newgene);

       // Mygenes[i+1].geneprint();//print the new gene


        best=Mygenes[i+1].bestchromo(arraynew,con_array);//find the best chromo of the gene
       // ff[i+1]=best;
        if(best<all_best)
        {
            all_best=best;
            best_g=Mygenes[i+1].idg;
            best_c=Mygenes[i+1].bestid;
            lifefrombest=bestlifetime;

        }

        else {

            lifefrombest--;
        }
      // cout<<"Life from best ( "<<all_best<<"_gene_"<<best_g<<" ) Remaining ... "<<lifefrombest<<" Genes"<<endl;

        if(better <= gbetter)
        {   //tlast
           // cout<<"comparison : "<<last<<" / "<<best<<endl;
            better=(last-best)/last;
            if(better<=gbetter)
            {
                lifet++;
            }
            else
            {
                lifet=0;
            }
        }
        else if(better > gbetter)
        {
            lifet=0;
            //cout<<"comparison : "<<last<<" / "<<best<<endl;
            better =(last-best)/last;
            if(better<=gbetter)
            {
                lifet++;
            }
            else
            {
                lifet=0;
            }

        }
      //  min__cut[i+1]=Mygenes[i+1].chromoVector[Mygenes[i+1].bestid].getmincut(arraynew,con_array);
       // sumquality[i+1]=Mygenes[i+1].chromoVector[Mygenes[i+1].bestid].getsum(arraynew,con_array);
      //  cout<<endl<<"balanced_par=(f-mean)/mean_gene_"<<i+2<<" x factor("<<factor<<" ) : "<<(Mygenes[i+1].chromoVector[Mygenes[i+1].bestid].getsum(arraynew,con_array)/mo)*factor<<endl;
       // cout<<"mincut=(m-pinsum)/pinsum_gene_"<<i+2<<" x (1-factor)( "<<1-factor<<" ) : "<<((Mygenes[i+1].chromoVector[Mygenes[i+1].bestid].getmincut(arraynew,con_array)-pinsum)/pinsum)*(1-factor);
      //  cout<<endl;
       /* cout<<"Pinsum (sum_of_intercon x"<<min_cut_percent<<") :"<<pinsum<<endl;
        cout<<"Factor : "<<factor<<endl;
        cout<<"f_f=factor x balanced_par + (1-factor) x min_cut"<<endl;
        cout<<endl;*/
       // cout<<"counting : "<<lifet<<endl<<"percentage of improvement : "<<better<<endl;
        i++;
//testfun(Mygenes[i].chromoVector[Mygenes[i].bestid].chromosome_array,arraynew,mo,con_array);
    }


    if(best_g!=1 && best>stde)
    {
        //print the best solution
        cout<<endl<<" __________________Best_Solution__________________"<<endl;
        //cout<<"-> array=    [ ";

      /*  for(int i=0; i<num; i++)
        {
            cout<<arraynew[i]<<" ";
        }
        cout<<" ] <-"<<endl;*/
        for(int j=0; j<num; j++)
        {
            finalsol[j]=Mygenes[best_g-2].chromoVector[best_c].chromosome_array[j];
        }

        Mygenes[best_g-2].chromoVector[best_c].chromoprint_final();

        cout<<endl;
        cout<<"___Chromosome_"<<best_c<<"_of_Gene_"<<best_g<<"_fit_fun = "<<all_best<<"___________"<<endl;
        cout<<"..........Distance_from_bound : "<<(all_best-stde)<<"................"<<endl;
    }


    else if(best_g!=1 && best<= stde)
    {
        cout<<endl<<" __________________Best_Solution__________________"<<endl;
       // cout<<"-> array=    [ ";

      /*  for(int i=0; i<num; i++)
        {
            cout<<arraynew[i]<<" ";
        }
        cout<<" ] <-"<<endl;*/

        for(int j=0; j<num; j++)
        {
            finalsol[j]=Mygenes[i].chromoVector[best_c].chromosome_array[j];
        }
        Mygenes[i].chromoVector[best_c].chromoprint_final();

        cout<<endl;
        cout<<"___Chromosome_"<<Mygenes[i].bestid<<"_of_Gene_"<<Mygenes[i].idg<<"_fit_fun = "<<best<<"___________"<<endl;

    }

    else if( best_g==1 )
    {

        cout<<endl<<" __________________Best_Solution__________________"<<endl;
       // cout<<"-> array=    [ ";

        /*for(int i=0; i<num; i++)
        {
            cout<<arraynew[i]<<" ";
        }
        cout<<" ] <-"<<endl;*/

        for(int j=0; j<num; j++)
        {
            finalsol[j]=Firstgene.chromoVector[best_c].chromosome_array[j];
        }
        Firstgene.chromoVector[best_c].chromoprint_final();

        cout<<endl;
        cout<<"___Chromosome_"<<best_c<<"_of_Gene_"<<best_g<<"_fit_fun = "<<f_best<<"___________"<<endl;
        cout<<"..........Distance_from_bound : "<<(all_best-stde)<<"................"<<endl;


    }



   testfun(finalsol,arraynew,mo,con_array,Firstgene.par);

   gettimeofday(&tim,NULL);
    double time2 = tim.tv_sec;




/*->*/

cout<<"Total Gene_Num: "<<i<<endl;
cout<<endl<<"********* Time of execution : "<<time2 -time1<<" sec  *********"<<endl;
/*
cout<<endl;
cout<<"___________________________________________________________________"<<endl;
cout<<"ff=[ ";
for(int k=0;k<Mygenes[i].idg-1;k++)
    {
        cout<<ff[k]<<",";
}
cout<<ff[Mygenes[i].idg-1]<<" ";
cout<<"]"<<endl;


cout<<"___________________________________________________________________"<<endl;
cout<<"Min_Cut=[ ";
for(int k=0;k<Mygenes[i].idg-1;k++)
    {
        cout<<min__cut[k]<<",";
}
cout<<min__cut[Mygenes[i].idg-1]<<" ";
cout<<"]"<<endl;
cout<<"___________________________________________________________________"<<endl;
cout<<"sums=[ ";
for(int k=0;k<Mygenes[i].idg-1;k++)
    {
        cout<<sumquality[k]<<",";
}
cout<<sumquality[Mygenes[i].idg-1]<<" ";
cout<<"]"<<endl;
cout<<"___________________________________________________________________"<<endl;

*/
    //Destruct all the chromosomes and genes

   /* for(unsigned int i=0; i<Mygenes.size(); i++)
    {

        Mygenes[i].~Gene();
    }
*/
    
 
    string s1="GA_Results_";
    s1+=to_string(num);
    s1+="_";
    s1+=argv[3];
    s1+="_";
    s1+=argv[5];
    s1+="_";
    s1+=argv[4];
    cout<<"==> Writing the Results"<<endl;
    ofstream MyFile(s1);
    for(int z=0;z<num;z++){
    MyFile<<finalsol[z]<<endl;
     
  }
   MyFile.close();
cout<<"==> File name:"<<s1<<endl;
  
    


    return 0;
}

