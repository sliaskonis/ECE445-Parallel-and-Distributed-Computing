#!/bin/bash

arr_sizes=(1024 4096 16384 65536) #262144 1048576
executables=(problem3 problem4)

mkdir -p results
make 

for exe in "${executables[@]}"; do
    for size in "${arr_sizes[@]}"; do
        echo "Running for ./$exe array size $size"
        echo "ArraySize=$size" >> "results/${exe}_out.txt"
        for i in {1..5}; do
            echo "Iteration $i" >> "results/${exe}_out.txt"
            ./"$exe" "$size" >> "results/${exe}_out.txt"
        done
    done
done

make clean
echo "All done"