#!/bin/bash
for i in `seq 1 100`
do
    if [ $((${i}%10)) -eq 0 ]
    then
        for num in `seq 1 9`
        do
            number=$((${i}-10+${num}))
            cat sample${number}.txt >> sample${i}.txt
        done
    fi
done