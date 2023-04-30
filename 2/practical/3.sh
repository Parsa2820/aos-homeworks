#!/bin/bash

TIMEOUT=3

echo "Running 3.sh"
echo "Stress with --cpu 10 for $TIMEOUT seconds"
perf stat --event page-faults,cache-misses,dTLB-load-misses,dTLB-loads,dTLB-stores stress --cpu 10 --timeout $TIMEOUT
echo "Stress with --vm 4 and --vm-bytes 512M for $TIMEOUT seconds"
perf stat --event page-faults,cache-misses,dTLB-load-misses,dTLB-loads,dTLB-stores stress --vm 4 --vm-bytes 512M --timeout $TIMEOUT
echo "Stress with --io 5 for $TIMEOUT seconds"
perf stat --event page-faults,cache-misses,dTLB-load-misses,dTLB-loads,dTLB-stores stress --io 5 --timeout $TIMEOUT
