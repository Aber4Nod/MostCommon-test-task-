#!/bin/bash

DIR=./tests/copies
echo
echo "Starting regular tests::Numbers_Only"
echo

for i in `seq 1 100`
do
    file=$(mktemp $DIR/TEST_REG_NUMBERS.XXXXXX)
    echo "Create a file: $file"
    for c in `seq 1 $(($i*10))`
    do
        echo $RANDOM  >> $file
    done
done

echo
echo "Starting regular tests::Chars_Only"
echo

for i in `seq 1 100`
do
    file=$(mktemp $DIR/TEST_REG_CHARS.XXXXXX)
    echo "Create a file: $file"
    for c in `seq 1 10`
    do
        cat /dev/urandom | tr -dc 'a-zA-Z' | fold -w $(shuf -i 1-$(($i*10)) -n 1) | head -n $(($c+$i)) >> $file
    done
done

echo
echo "Starting regular tests::Symbols_Only"
echo

for i in `seq 1 100`
do
    file=$(mktemp $DIR/TEST_REG_SYMBOLS.XXXXXX)
    echo "Create a file: $file"
    for c in `seq 1 10`
    do
        cat /dev/urandom | tr -dc '~`!@#$%^&*()-+?.,|\/"' | fold -w $(shuf -i 1-$(($i*10)) -n 1) | head -n $(($c+$i)) >> $file
    done
done
