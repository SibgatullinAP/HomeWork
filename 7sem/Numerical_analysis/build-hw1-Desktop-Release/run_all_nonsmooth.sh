#!/bin/bash

#for MU in 0.1
#do
#        ./hw_1_nonsmooth_1 10. 1. 1000 1000 $MU 1 1.4 135887 3&
#        ./hw_1_nonsmooth_1 10. 1. 1000 1000 $MU 1 1 134174 3&
#        ./hw_1_nonsmooth_1 10. 1. 1000 1000 $MU 10 1 163945 3&
#done


#for MU in 0.01
#do
#        ./hw_1_nonsmooth_1 10. 1. 1000 1000 $MU 1 1.4 919329 3&
#        ./hw_1_nonsmooth_1 10. 1. 1000 1000 $MU 1 1 943130 3&
#        ./hw_1_nonsmooth_1 10. 1. 1000 1000 $MU 10 1 1482963 3&
#done


for MU in 0.01
do
        ./hw_1_nonsmooth_1 10. 1. 1000 1000 $MU 1 1.4 2495754 3&
        ./hw_1_nonsmooth_1 10. 1. 1000 1000 $MU 1 1 2541365 3&
        ./hw_1_nonsmooth_1 10. 1. 1000 1000 $MU 10 1 5197349 3&
done

for MU in 0.1
do
        ./hw_1_nonsmooth_1 10. 1. 1000 1000 $MU 1 1.4 400812 3&
        ./hw_1_nonsmooth_1 10. 1. 1000 1000 $MU 1 1 414338 3&
        ./hw_1_nonsmooth_1 10. 1. 1000 1000 $MU 10 1 444219 3&
done
