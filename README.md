# Big Integer (in C)

This is a barebones implementation of the famous Java class called BigInteger, that allows operations on arbitrarly large integer values.

## Architecture

We have a type struct, called `big_int_t` that can be constructed using any of the integer variants, either unsigned, signed, 8, 16, 32 and 64 bits long.

## TODO List

[x] - Generic construction

[x] - Addition

[] - Subtraction

[] - Comparisson

[] - Multiplication

[] - Division

[] - Add examples

## Tests

We don't use any proper testing framework, anytime we want to add new tests, you can just add a new file inside the `/tests` directory, and add it to the `run-test.sh` script, then you can just `$ ./run-test.sh` and run all of your tests :P
