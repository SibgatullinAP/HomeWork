#!/bin/bash

for MU in 0.1 0.01
do
        ./hw_1_flow 10. 1. 1000 1000 $MU 1 1 10000&
        ./hw_1_flow 10. 1. 1000 1000 $MU 10 1 10000&
        ./hw_1_flow 10. 1. 1000 1000 $MU 1 1.4 10000&
done
