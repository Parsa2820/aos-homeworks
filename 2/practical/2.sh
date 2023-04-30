#!/bin/bash

gcc -o 2 2.c -lpthread

for mode in "SYNC" "ASYNC"
do
    echo "Running 2 with $mode"
    perf stat --event page-faults,cache-misses,dTLB-load-misses,dTLB-loads,dTLB-stores ./2 $mode
    echo "-----------------"
done
