#!/bin/bash

if [ ! -d ./tests/tmp/ ]; then
    mkdir ./tests/tmp/
else
    rm -f ./tests/tmp/*
fi
if [ ! -d ./tests/copies/ ]; then
    mkdir ./tests/copies/
else
    rm -f ./tests/copies/*
fi
if [ ! -d ./res/ ]; then
    mkdir ./res/
else
    rm -f ./res/*
fi

