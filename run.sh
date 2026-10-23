#!/bin/bash

EXE="./wbp-solver"

if [[ $# -ne 1 || ! $1 =~ ^[0-9]+$ ]]; then
    echo "Usage: $0 <number-of-tests>" >&2
    exit 1
fi

shopt -s nullglob
TEST_FILES=("./test"/*)

# Keep only regular files.
files=()
for filename in "${TEST_FILES[@]}"; do
    [[ -f "$filename" ]] && files+=("$filename")
done

NUM_TEST_FILES=${#files[@]}
limit=$((10#$1))

if (( limit > NUM_TEST_FILES )); then
    limit=$NUM_TEST_FILES
fi

echo "Running first $limit tests from $NUM_TEST_FILES ..."
echo ""

for ((i = 0; i < limit; i++)); do
    filename="${files[i]}"
    
    echo "------------------------------"
    echo "[$((i + 1))]: $filename"
    echo "------------------------------"
    echo ""
    "$EXE" < "$filename"
    echo ""
done