#!/bin/bash

FILE=./tests/tmp/*
err=./errors
for file in $FILE
do
    if [ -f "$file" ]; then
        linePr=''
        echo "Checking file: $file"
        while IFS=='' read -r line || [[ -n $line ]];
        do
            if [ "$linePr" != "" ] && [ "$linePr" \< "$line" ]; then
                echo "$file::mergesort phase failed: $linePr < $line"
                echo "Error::Processing phase::$file" >> $err
                echo "$file::MergeSort error" >> $err
                echo "$linePr < $line" >> $err
                exit
            fi
            linePr=$line
        done < $file
        DIFF=$(diff <(cat $(find ./res -regextype posix-extended -regex ".*/$(basename $file)\..{6}") | awk '{print $2}') <(cat $(find ./tests/copies -regextype posix-extended -regex ".*/$(basename $file)") | sort | uniq -c | sort -n -r | head -n 10 | awk '{print $1}'))
        if [ "$DIFF" != "" ]; then
            echo "$file::frequency phase failed"
            echo "Error::Processing phase::$file" >> $err
            echo "$file::Frequency error" >> $err
            echo $DIFF >> $err
            exit
        fi
        echo "$file::OK"
    fi
done

