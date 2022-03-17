#!/bin/bash
echo 'Help :';
echo 'first argument : number of nodes (current value :'$1')';
echo 'second argument : number of parts(current value :'$2')';
echo 'third argument : density number (current value :'$3')';
echo 'fourht argument : test id (current value :'$4')';
echo 'fifth argument : nodes file name (current value :'$5')';
echo 'sixth argument : edges file name (current value :'$6')';

echo 'Starting' ;

lifetime=0;
gbetter=0;
mincutper=0;

if [ $1 -lt  500 ] ; then 
 if [ $2 -lt 3 ] ; then 
  lifetime=75;
  gbetter=0.00065;
  mincutper=0.4;
 elif [ $2 -lt 4 ] ; then
  lifetime= 75;
  gbetter=0.00065;
  mincutper=0.6;
 elif  [ $2 -lt 6 ] ; then
  lifetime=75;
  gbetter=0.00065;
  mincutper=0.7;
 elif [ $2 -lt 8 ] ; then 
  lifetime=70;
  gbetter=0.00065;
  mincutper=0.8;
 elif [ $2 -lt 11] ; then 
  lifetime=65;
  gbetter=0.00065;
  mincutper=1.6;
 else
  echo '====> Untested partitioning!! For better results  please try a custom selection of parameters values using g++ and ./';
  lifetime=65;
  gbetter=0.00065;
  mincutper=1.6;
 fi
elif [ $1 -lt 800 ] ; then 
 if [ $2 -lt 3 ] ; then 
  lifetime=65;
  gbetter=0.0065;
  mincutper=0.4;
 elif [ $2 -lt 4] ; then
  lifetime=65;
  gbetter=0.0065;
  mincutper=0.6;
 elif  [ $2 -lt 6 ] ; then
  lifetime=65;
  gbetter=0.0065;
  mincutper=0.7;
 elif [ $2 -lt 8 ] ; then 
  lifetime=55;
  gbetter=0.0065;
  mincutper=0.8;
 elif [ $2 -lt 11] ; then 
  lifetime=50;
  gbetter=0.0065;
  mincutper=1.6;
 else
   echo '====> Untested partitioning!! For better results  please try a custom selection of parameters values using g++ and ./';
  lifetime=50;
  gbetter=0.0065;
  mincutper=1.6;
 fi
elif [ $1 -lt 1600 ] ; then 
 if [ $2 -lt 3 ] ; then 
  lifetime=55;
  gbetter=0.0065;
  mincutper=0.4;
 elif [ $2 -lt 4 ] ; then
  lifetime=55;
  gbetter=0.0065;
  mincutper=0.6;
 elif  [ $2 -lt 6 ] ; then
  lifetime=55;
  gbetter=0.0065;
  mincutper=0.7;
 elif [ $2 -lt 8 ] ; then 
  lifetime=45;
  gbetter=0.0065;
  mincutper=0.8;
 elif [ $2 -lt 11 ] ; then 
  lifetime=40;
  gbetter=0.0065;
  mincutper=1.6;
 else
  echo '====> Untested partitioning!! For better results  please try a custom selection of parameters values using g++ and ./';
  lifetime=40;
  gbetter=0.0065;
  mincutper=1.6;
 fi
else 
echo '===> Untested number of nodes!! For better results please try custom selection of parameters values using g++ and ./'
if [ $2 -lt 3 ] ; then 
  lifetime=55;
  gbetter=0.0065;
  mincutper=0.4;
 elif [ $2 -lt 4 ] ; then
  lifetime=55;
  gbetter=0.0065;
  mincutper=0.6;
 elif  [ $2 -lt 6 ] ; then
  lifetime=55;
  gbetter=0.0065;
  mincutper=0.7;
 elif [ $2 -lt 8 ] ; then 
  lifetime=45;
  gbetter=0.0065;
  mincutper=0.8;
 elif [ $2 -lt 11 ] ; then 
  lifetime=40;
  gbetter=0.0065;
  mincutper=1.6;
 else
   echo '====> Untested partitioning!! For better results  please try a custom selection of parameters values using g++ and ./';
  lifetime=40;
  gbetter=0.0065;
  mincutper=1.6;
 fi
fi



g++  -fopenmp -Dpopnum=$1 -Dthelifetime=$lifetime -Dmincutper=$mincutper -Dthegbetter=$gbetter -Wall Chromosome.cpp Gene.cpp main.cpp Chromosome.h Gene.h  -o GA ;

echo ;
echo 'Starting the execution of GA...';
./GA  $5 $6 $3 $4 $2 ;

