#!/usr/bin/env bash

DIR="./magma"
OUT_MAG="outs"
OUT_FGB="fgb_outs"

function read_magma_mem {
  i=1
  q=$1
  n=$2

  for val in $(cat $DIR"/"$OUT_MAG"/out_q"$q"_n"$n".txt"); do
    if [[ i -eq 4 ]]; then
      echo $(($val / 1000)) && return
    fi
    i=$(($i + 1))
  done
}

function read_magma_cpu {
  i=1
  q=$1
  n=$2

  for val in $(cat $DIR"/"$OUT_MAG"/out_q"$q"_n"$n".txt"); do
    if [[ i -eq 3 ]]; then
      echo $val && return
    fi
    i=$(($i + 1))
  done
}

function read_fgb_mem {
  i=1
  q=$1
  n=$2

  for val in $(cat $DIR"/"$OUT_FGB"/output_q"$q"_n"$n); do
    if [[ i -eq 4 ]]; then
      echo $val && return
    fi
    i=$(($i + 1))
  done
}

function read_fgb_cpu {
  i=1
  q=$1
  n=$2

  for val in $(cat $DIR"/"$OUT_FGB"/output_q"$q"_n"$n); do
    if [[ i -eq 3 ]]; then
      echo $val && return
    fi
    i=$(($i + 1))
  done
}

primes=( 2 3 5 7 11 13 17 19 23 29 31 37 )

for q in "${primes[@]}"; do
  aux_cpu="{ label : 'fgb', values : ["
  aux_mem="{ label : 'fgb', values : ["
  cpu="var cpu"$q" = [ { label : 'magma', values : ["
  mem="var mem"$q" = [ { label : 'magma', values : ["
  for n in $(seq 2 11); do
    cpu+=" { x : "$n", y : "$(read_magma_cpu $q $n)" },"
    aux_cpu+=" { x : "$n", y : "$(read_fgb_cpu $q $n)" },"
    mem+=" { x : "$n", y : "$(read_magma_mem $q $n)" },"
    aux_mem+=" { x : "$n", y : "$(read_fgb_mem $q $n)" },"
  done
  cpu+=" ] }, "$aux_cpu" ] } ];"
  mem+=" ] }, "$aux_mem" ] } ];"
  echo $cpu >> html/assets/js/data.js
  echo $mem >> html/assets/js/data.js
done

exit 0
