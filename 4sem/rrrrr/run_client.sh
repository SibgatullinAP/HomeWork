#!/bin/bash

host="127.0.0.1"
dir="/home/pam/dz/tests"

for ((port=20801; port <= 20804; port ++))
  do
    (
      echo "Connecting to host=${host} port=${port}"
      ./client ${host} ${port} < "${dir}/commands6.txt"     >  res-${port}
      ./client ${host} ${port} < "${dir}/init_commands.txt" >> res-${port}
      for ((i=0;i<20;i++))
        do
          ./client ${host} ${port} < "${dir}/client_commands.txt" > res-${port}-${i} &
        done
      wait
      ./client ${host} ${port} < "${dir}/finish_commands.txt"
      echo "------------------------------------------------------------"
    ) &
  done

wait

for ((port=20801; port <= 20804; port ++))
  do
    result_init=`grep '^ *Student' res-${port} | wc -l`
    result=`grep '^ *Student' res-${port}-0 | wc -l`
    for ((i=1;i<20;i++))
      do
        diff -q res-${port}-0 res-${port}-${i}
      done
    echo "For port=${port} init=${result_init} answer=${result}"
    echo "------------------------------------------------------------"
  done

