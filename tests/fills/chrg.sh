#!/bin/bash
DIR=./tests/copies
for i in `seq 1 100`
do
    file=$(mktemp $DIR/TEST_MIX_SMALL_DIFFLNG.XXXXXX)
    echo "Create a file: $file"
    for c in `seq 1 5`
    do
        cat /dev/urandom | tr -dc 'a-zA-Z0-9~`!@#$%^&*()-+?.,|\/"' | fold -w $(shuf -i 1-$(($c*100)) -n 1) | head -n $i >> $file
    done
done
