#!/bin/bash

echo "Clean all binaries..."
make clean > /dev/null
make tsc_precision raw_precision > /dev/null
echo "Measuring TSC Precision..."
./tsc_precision
echo "Measuring RAW Precision..."
./raw_precision
