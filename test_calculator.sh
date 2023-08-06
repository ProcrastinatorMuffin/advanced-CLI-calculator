#!/bin/bash

# Function to test the calculator
test_calculator() {
    input=$1
    expected_output=$2
    mode=$3 # "result" or "error"

    # Run the calculator with the provided input and capture the output
    if [ "$mode" == "result" ]; then
        output=$(echo -e "$input" | ./calculator | grep "Result")
    else
        output=$(echo -e "$input" | ./calculator | grep "Error")
    fi

    # Check if the result matches the expected output
    if [[ $output == *"$expected_output"* ]]; then
        echo "Test passed!"
    else
        echo "Test failed! Expected: $expected_output, but got: $output"
    fi
}

# Compile the calculator
gcc calculator.c -o calculator

# Test addition
test_calculator "1\n5\n10\n5\n" "Result: 15.000000" "result"
# Test subtraction
test_calculator "2\n15\n5\n5\n" "Result: 10.000000" "result"
# Test multiplication
test_calculator "3\n5\n5\n5\n" "Result: 25.000000" "result"
# Test division
test_calculator "4\n10\n2\n5\n" "Result: 5.000000" "result"
# Test division by zero
test_calculator "4\n10\n0\n5\n" "Error: Division by zero." "error"
# Test invalid choice
test_calculator "6\n5\n" "Invalid choice!" "error"
# Test input with comma instead of dot
test_calculator "1\n5,5\n10\n5\n" "Error" "error"
