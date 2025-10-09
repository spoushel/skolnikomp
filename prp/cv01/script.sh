#!usr/bin/env bash
seq 1 1 10 > numbers.txt
cat numbers.txt
cat numbers.txt | shuf > random_numbers.txt