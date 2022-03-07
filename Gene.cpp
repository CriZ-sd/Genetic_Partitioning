#include "Gene.h"
#include "Chromosome.h"


//Empty constructor
Gene::Gene()
{
    idg=0;
    numofchromos=0;
    threshold=0;
}


//Constructor for first gene (not using a Chromosome Vector)
Gene::Gene(int id,int chromonum,double thres)
{
    idg=id;
    numofchromos=chromonum;
    threshold=thres;
}

//Constructor for new genes (using a Chromosome Vector )
Gene::Gene(int id,int chromonum,double thres,vector<Chromosome> chr)
{
    idg=id;
    numofchromos=chromonum;
    threshold=thres;
    for(int i=0; i<chromonum; i++)
    {

        chromoVector.push_back(chr[i]);
    }

}


//Destructor , using the Chromosome destructor for every Chromosome of the Gene
Gene::~Gene()
{
    for(int i=0; i<numofchromos; i++)
    {
        chromoVector[i].~Chromosome();
        newGen[i].~Chromosome();
    }



}
