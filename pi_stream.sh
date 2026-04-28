#!/bin/sh

n=1

while :
do
	./pi $n
	n=$(expr $n + 1)
done
