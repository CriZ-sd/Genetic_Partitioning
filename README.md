# Genetic_Partitioning

This repo includes the code for the partitioning genetic aglorithm 

To run an example you need a nodes file and an edges file.

nodes file:
a simple (txt) file with the nodes' weights 
____________________________________
node_0 weight 

node_1 weight

node_2 weight
.

.

.

.

.

__________________________________


**************************************

edges file:

a simple (txt) file with the edges' weights
__________________________________

edge_1_0 weight

edge_2_0 weight

edge_2_1 weight

edge_3_0 weight

edge_3_1 weight

edge_3_2 weight

.

.

.

.

.

__________________________________


Inside the repo you can find the files GA_nodes_1000_0 and GA_edges_1000_0 which are example files for a fully connected graph with 1000 nodes. 

-------------------------------------------------------------------------------------------------------------------------------------------------------

To run an example in linux :

You can use the prepaired script: 

1. chmod +x GA_run.sh

2. ./GA_run.sh nn pp dd cc xxxxxx yyyyyyy 

(nn : integer number of nodes

 pp : integer number of parts 
 
 dd : density number (float just for the results files name-doesn't affect the result)
 
 cc : test id number (integer just for the results files name-doesn't affect the result)
 
xxxxxx : nodes file name

yyyyyyy : edges file name )

*********************************************************************************************

To run the 1000_0 example for 3 parts  through the script :

./GA_run.sh 1000 3 0 1 GA_nodes_100_0 GA_edges_1000_0 


------------------------------------------------------------------------------------------------------------------------------------------------------------
To run an example with custom parameters' values :

1. g++  -fopenmp -Dpopnum=number_of_nodes -Dthelifetime=... -Dmincutper=... -Dthegbetter=... -Wall Chromosome.cpp Gene.cpp main.cpp Chromosome.h Gene.h  -o GA ;

#for the parameters values see the LUT with the parameters -or- choose custom values

2. ./GA nodes_file edges_file density_number test_number number_of_parts

#density_number ={0,0.25,0.50,0.75} (0=fully connected, 0.25=0.75*fully connected,0.50=0.5* fully connected, 0.75=0.25* fully connected)

#test_number = integer from 0 to inf (doesn't affect the execution, just for  the name of the results' files)

#number_of_parts = integer from 2 to 10 (number of parts to partition the graph , you can try mire than 10 but only till 10 are tested the parameters)

-------------------------------------------------------------------------------------------------------------------------------------------------------
To  run the 1000_0 example with custom parameters values run:

1. g++  -fopenmp -Dpopnum=$ncount -Dthelifetime=55 -Dmincutper=...  -Dthegbetter=0.0065 -Wall Chromosome.cpp Gene.cpp main.cpp Chromosome.h

#Dmincutper: 2-parts->0.4 , 3-parts -> 0.6, 4,5-parts-> 0.7 , 6,7-parts-> 0.8 , 8,9,10-parts -> 1.6 -or- choose custom values for all the parameters

2. ./GA GA_nodes_1000_0 GA_edges_1000_0 0 1 2 #(or 3,4,...10) 



