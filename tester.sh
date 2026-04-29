#! /usr/bin/env bash

# we wont test formatted output as the original function tends to use columns and that is not mandatrory to implement in this version
# therefore any run tests run on ls -l  to force one entry per line to be comparable

compare(){
    mkdir temp
    $(ls $1 > temp/orig)
    $(./ft_ls $1 > temp/mine)
    diff temp/orig temp/mine
}

compare "-l"