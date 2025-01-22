#!/bin/bash
iterations=100

# Main script logic
main() {
    serial=$1
    n=$2
    p=$3

    echo "Starting measurements with arguments: $serial, $n, $p"
    
    if($serial); then
        total_time=0
        echo "Running measurements in serial mode"
        for ((i=1; i<=iterations; i++)); do
            output=$(./ask4_ser $2)
            elapsed_time=$(echo "$output" | grep -oP 'Elapsed time: \K[0-9]+\.[0-9]+')
            total_time=$(echo "$total_time + $elapsed_time" | bc)
        done
        average_time="0$(echo "scale=13; $total_time / $iterations" | bc -l)"
        average_time=$(printf "%13s" $average_time)
        echo "Average elapsed time: $average_time"
    else
        echo "Running measurements in parallel mode"
        total_time=0
        echo "Running measurements in parallel mode with $p processes"
        for ((i=1; i<=iterations; i++)); do
            output=$(mpirun -np $p ask4_par $n )
            elapsed_time=$(echo "$output" | grep -oP 'Elapsed time: \K[0-9]+\.[0-9]+')
            total_time=$(echo "$total_time + $elapsed_time" | bc)
        done
        average_time="0$(echo "scale=13; $total_time / $iterations" | bc -l)"
        average_time=$(printf "%13s" $average_time)
        echo "Average elapsed time: $average_time"
    fi

    echo "Measurements completed."
}

# Function to display usage information
usage() {
    echo "Usage: $0 [options]"
    echo "Options:"
    echo "  -s, --serial    [n]     Run measurements in serial mode"
    echo "  -p, --parallel  [n] [p] Run measurements in parallel mode"
    echo "  -i, --iter      [i]     Number of iterations to run the measurements (before -s/-p)"
    echo "  -h, --help              Show this help message and exit" 
}

# Parse command line arguments
while [[ "$#" -gt 0 ]]; do
    case $1 in
        -h|--help) usage; exit 0 ;;
        -s|--serial) shift; main true $1 0; exit 0 ;;
        -p|--parallel) shift; main false $1 $2; exit 0 ;;
        -i|--iter) shift; iterations=$1 ;;
        *) echo "Unknown parameter passed: $1"; usage; exit 1 ;;
    esac
    shift
done

