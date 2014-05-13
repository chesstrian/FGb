#!/usr/bin/env bash

DIR="./magma"

primes=( 2 3 5 7 11 13 17 19 23 29 31 37 )

for q in "${primes[@]}"
do
  for n in $(seq 2 12)
  do
    fgb=$(sed -e 's/+/ + /g' -e 's/ 1\*/ /g' -n -e '1x;1!H;${x;s-\n- -gp}' $DIR"/fgb_sols/solution_q"$q"_n"$n | tr -s ' ')
    mag=$(sed -e $'s/\r$//' -n -e '1x;1!H;${x;s-\n- -gp}' $DIR"/sols/sol_q"$q"_n"$n".txt" | tr -s ' ')

    if [ "$fgb" != "$mag" ]
    then
      echo "q=$q ---- n=$n"
    fi
  done
done

exit 0

