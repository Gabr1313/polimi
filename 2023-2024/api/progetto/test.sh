#!/usr/bin/bash

# gcc -DEVAL -Wall -Werror -std=gnu11 -O2 -pipe -static -s Open.c

make perf F=$1
for ((i = 1; i <= 11; i++)) do
    { time ./a.out <test/open${i}.txt >out.txt; } 2> /tmp/time.txt
    real_time=$(grep real /tmp/time.txt | awk '{print $2}')
    printf "Time %2d: %s\n" $i $real_time
    diff -q out.txt test/open${i}.output.txt
done

# make perf F=main.no-black-magic.c
# for ((i = 1; i <= 11; i++)) do
#     { time ./a.out <test/open${i}.txt >out.txt; } 2> /tmp/time.txt
#     real_time=$(grep real /tmp/time.txt | awk '{print $2}')
#     printf "Time %2d: %s\n" $i $real_time
#     diff -q out.txt test/open${i}.output.txt
# done


# make c++ F=main.cpp
# for ((i = 1; i <= 11; i++)) do
#     { time ./a.out <test/open${i}.txt >out.txt; } 2> /tmp/time.txt
#     real_time=$(grep real /tmp/time.txt | awk '{print $2}')
#     echo "Time $i: $real_time"
#     diff -q out.txt test/open${i}.output.txt
# done
