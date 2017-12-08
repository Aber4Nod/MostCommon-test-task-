#!/bin/bash

FILE=./tests/tmp/*
file=t
numthr=$1

for flin in $FILE
do
    if [ -f "$flin" ]; then
        echo "evaluating: $flin by $numthr threads"
        ./$file $flin $numthr > /dev/null
    fi
done
