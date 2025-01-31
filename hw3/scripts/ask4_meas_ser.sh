#!/bin/bash

nlimit=3000
file="../results/meas_ask4_ser.csv"

rm -f $file
touch $file

for ((n=100; n<=nlimit; n=n+100)); do
    echo -n "${n}," >> $file
done
echo "" >> $file

for ((n=100; n<=nlimit; n=n+100)); do
    echo "Running for n = $n"
    output=$(./ask4_meas.sh -i 100 -s $n)
    elapsed_time=$(echo "$output" | grep -oP 'Average elapsed time: \K[0-9]+\.[0-9]+')
    elapsed_time=$(echo "$elapsed_time * 1000" | bc)
    elapsed_time=$(printf "%8s" $elapsed_time)
    echo -n "0${elapsed_time}," >> $file
done
echo "Done!"
echo "" >> $file
