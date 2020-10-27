#!/bin/bash

#n=1000000
#n=5000000
n=10000000

dir="/home/pam/dz/tests"
data="\
a${n}.txt \
a${n}_sort_g.txt \
a${n}_sort_n.txt \
a${n}_sort_v.txt \
"

commands="\
commands_1000000_v.txt \
commands_1000000_g.txt \
commands4.txt \
"


for data in ${data}
  do \
    for cmd in ${commands}
      do \
        data_file="${dir}/${data}"
        cmd_file="${dir}/${cmd}"
        echo "Data=${data_file} Commands=${cmd_file}"
        time=$(date +%s)
        result=`cat ${cmd_file} | ./a.out ${data_file} 1000 1000 | grep ':'` 
        echo "$result"
        echo "All time : $(($(date +%s)-$time))"
        echo "------------------------------------------------------------"
      done
  done
