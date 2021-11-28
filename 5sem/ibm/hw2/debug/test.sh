#!/bin/bash

echo "" > tmp.txt

for i in 20
do 

for ((j=1; j <= $i; j++ ))
do
echo "$i $j" >> log.txt $(./a.out $i $j 1 1 | grep "Solving time: ") >> tmp.txt

echo "$i $j" >> log.txt $(./a.out $i $j 1 2 | grep "Solving time: ") >> tmp.txt

echo "$i $j" >> log.txt $(./a.out $i $j 1 3 | grep "Solving time: ") >> tmp.txt
done 

done 

cut -d " " -f '1 2 6' tmp.txt > log.txt

