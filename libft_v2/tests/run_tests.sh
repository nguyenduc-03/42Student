#!/bin/bash

# Path to the directory where the executables are located (outside the tests directory)
exec_dir="../"  # Adjust this path according to where your executables are stored

# Automatically gather all test executables (not source or object files) from the exec_dir
test_programs=$(ls $exec_dir/test_*)

# Compile and run each test
for test_prog in $test_programs; do
    echo "Running $test_prog..."
    if ./$test_prog; then
        echo "$test_prog passed!"
    else
        echo "$test_prog failed!"
    fi
    echo "--------------------"
done
