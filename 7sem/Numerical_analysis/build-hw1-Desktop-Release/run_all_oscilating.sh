#!/bin/bash

for MU in 0.1 0.01
do
        ./hw_1_oscilating 1. 1. 10000 100 $MU 1 1 8&
        ./hw_1_oscilating 1. 1. 10000 100 $MU 10 1 8&
        ./hw_1_oscilating 1. 1. 10000 100 $MU 1 1.4 8&
done
