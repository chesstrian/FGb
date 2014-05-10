#!/usr/bin/env bash

EXE="./main"
DIR="./magma"

primes=( 2 3 5 7 11 13 17 19 23 29 31 37 )

for q in "${primes[@]}"
do
  for n in $(seq 2 13)
  do
    $EXE $DIR"/pols/pol_q"$q"_n"$n".txt" $n $q 1
  done
done

exit 0

