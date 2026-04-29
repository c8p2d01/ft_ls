#! /usr/bin/env bash

function compile() {
    make -Cs ..
}

function test() {
    ls -l $1 | awk '{print $9}' > original.txt
    ./../ft_ls -l $1  | awk '{print $9}' > mine.txt
    diff original.txt mine.txt |cat -vET
    rm original.txt
    rm mine.txt
}

test -a

