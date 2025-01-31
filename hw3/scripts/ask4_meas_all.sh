#!/bin/bash

nlimit=3000
declare -a pvals=(2 4 5 10)
file="../results/meas_ask4.csv"

rm -f $file
touch $file

echo -n "Num_Processors," >> $file
for ((n=100; n<=nlimit; n=n+100)); do
    echo -n "${n}," >> $file
done
echo "" >> $file

for ((i=0; i<4; i++)); do
    echo "Running measurements in parallel mode with ${pvals[i]} processes"
    echo -n "${pvals[i]}," >> $file
    for ((n=100; n<=nlimit; n=n+100)); do
        echo "n = $n"
        output=$(./ask4_meas.sh -i 5 -p $n ${pvals[i]})
        elapsed_time=$(echo "$output" | grep -oP 'Average elapsed time: \K[0-9]+\.[0-9]+')
        elapsed_time=$(echo "$elapsed_time * 1000" | bc)
        elapsed_time=$(printf "%8s" $elapsed_time)
        echo -n "0${elapsed_time}," >> $file
    done
    echo "" >> $file
done


