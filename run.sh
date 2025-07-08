#!/bin/sh

# This script compiles the C++ code, runs the program with the specified arguments,
# cleans up the generated files after execution and runs the plotter

g++ main.cpp -o main -std=c++20

if [[ "$#" -lt 4 || "$#" -gt 6 ]]; then
    echo "Usage: $0 <min> <max> <n_samples>                 (uniform distribution)"
    echo "Usage: $0 <min> <max> <lambda> <n_samples>        (poisson distribution)"
    echo "Usage: $0 <min> <max> <mu> <sigma> <n_samples>    (normal distribution)"
    exit 1
fi

min=$1
max=$2

if [ "$#" -eq 5 ]; then
    lambda=$3
    n_samples=$4

    ./main $min $max $lambda $n_samples

elif [ "$#" -eq 6 ]; then
    mu=$3
    sigma=$4
    n_samples=$5

    ./main $min $max $mu $sigma $n_samples

else
    n_samples=$3

    ./main $min $max $n_samples
fi

# run the plotter

python3 plotter.py

# clean up generated files

rm -f main 
rm -f *.dat