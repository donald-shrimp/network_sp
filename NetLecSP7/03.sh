#!/bin/bash
for i in 10 20 30 40 50 60 70 80 90 100
do
day=`date`
echo ${day} >> sample${i}.txt
done