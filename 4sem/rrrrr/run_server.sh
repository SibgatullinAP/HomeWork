#!/bin/bash

#n=1000000
n=5000000

dir="/home/pam/dz/tests"

data="\
a${n}.txt \
a${n}_sort_g.txt \
a${n}_sort_n.txt \
a${n}_sort_v.txt \
"

echo "In ${PWD##*/} running ./server ${data_file} $* port"

port=20800
for data in ${data}
  do \
        data_file="${dir}/${data}"
        ((port++))
        export LEAKTRACE_FILE="server-port-${port}.leak"
        log="server-port-${port}.log"
        echo "Data=${data_file} port=${port} leak=${LEAKTRACE_FILE} log=${log}"
       ./server ${data_file} 10000 $* $port &> ${log} &
        echo "------------------------------------------------------------"
  done
wait

for ((port=20801; port <= 20804; port ++))
  do
    log="server-port-${port}.log"
    grep leak "$log"
  done
