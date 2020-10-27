#!/bin/bash

dir="/home/pam/dz/tests"

./client 127.0.0.1 5555 < "${dir}/init_commands.txt"

for ((i=0;i<1000;i++))
  do \
    ./client 127.0.0.1 5555 < "${dir}/client_commands.txt" > res$i &
  done
wait

./client 127.0.0.1 5555 < "${dir}/finish_commands.txt"

for ((i=0;i<1000;i++))
  do \
    for ((j=0;j<i;j++))
      do \
        diff -q res$i res$j
      done
    grep '^ *Student' res$i | wc
  done
