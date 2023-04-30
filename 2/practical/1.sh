#!/bin/bash

gcc -o 1 1.c -lphtread

for i in {1..7}
do
    echo "Running 1 with $i threads"
    perf stat --event page-faults,cache-misses,dTLB-load-misses,dTLB-loads,dTLB-stores ./1 $1 > /dev/null
    echo "-----------------"
done
