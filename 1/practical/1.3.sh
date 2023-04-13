#!/bin/bash

gcc -o 1.3 1.3.c

for i in {1..7}
do
    echo "Running 1.3 with $i threads"
    perf stat --event page-faults,cache-misses,dTLB-load-misses,dTLB-loads,dTLB-stores ./1.3 $1 > /dev/null
    echo "-----------------"
done
