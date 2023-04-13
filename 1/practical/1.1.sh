#!/bin/bash

function compile_with_page_size {
    echo "Compiling with page size $1"
    gcc -o 1.1 1.1.c -DPAGE_SIZE=$1
}

function run_with_params {
    echo "Running $1"
    perf stat --event page-faults,dTLB-load-misses,dTLB-loads,dTLB-stores ./1.1 $1
    echo "-----------------"
}

echo "Running 1.1"
echo "Running with page size 4096"
compile_with_page_size 4096
run_with_params alef
run_with_params be
run_with_params jim

echo "Running with page size 1024"
compile_with_page_size 1024
run_with_params alef
run_with_params be
run_with_params jim
