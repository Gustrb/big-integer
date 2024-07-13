#!/bin/bash

mkdir -p bin

FLAGS=-'Wall -Wextra -pedantic'
LIB='bin/bigint.o'
TEST_LIB='bin/test_utils.o'

echo 'Building the src/bigint.c library...'
gcc src/bigint.c -o $LIB -c $FLAGS
echo "Library build. Object file dumped to $LIB"

echo 'Building test library...'
gcc test/utils.c -o $TEST_LIB -c $FLAGS
echo "Finished building test library. Object file dumped to $TEST_LIB"

echo 'Building test cases...'
gcc test/byte-order.c -o bin/byteorder $LIB $TEST_LIB $FLAGS
gcc test/sum.c -o bin/sum $LIB $TEST_LIB $FLAGS
gcc test/sub.c -o bin/sub $LIB $TEST_LIB $FLAGS
echo 'Finished building all test cases'

echo 'Running tests...'
./bin/byteorder
./bin/sum
./bin/sub
echo 'All tests ran :P'
