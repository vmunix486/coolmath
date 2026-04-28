#!/bin/sh
#
# pibench.sh - Rough benchmark on CPU speed. Is basically just a list of commands and not a real shell script.
#
# NOTE: requires the time command

echo "Computing 1 digit..."
echo ""
time ./pi 1

echo "Computing 10 digits..."
echo ""
time ./pi 10

echo "Computing 50 digits..."
echo ""
time ./pi 50

echo "Computing 100 digits..."
echo ""
time ./pi 100

echo "Computing 500 digits..."
echo ""
time ./pi 500

echo "Computing 1000 digits..."
echo ""
time ./pi 1000
