#!/bin/bash

function compile_with_param {
    echo "Compiling with param $1"
    gcc -o 1.2 1.2.c -D$1
}

function run_with_params {
    echo "Running $1"
    perf stat --event page-faults,dTLB-load-misses,dTLB-loads,dTLB-stores ./1.2 $1
    echo "-----------------"
}

echo "Running 1.2"
echo "Running with normal thread b"
compile_with_param NOALT
run_with_params alef
run_with_params be
run_with_params jim

echo "Running with alternative thread b implementation"
compile_with_param ALT
run_with_params alef
run_with_params be
run_with_params jim
