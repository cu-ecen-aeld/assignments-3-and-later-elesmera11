#!/bin/bash -e

if [ $# -ne 2 ]; then
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi


path=$(dirname "$1")
filename=$(basename "$1")
if [ ! -e "$path" ]; then
    mkdir -p "$path" 
fi

if [ ! -e "$1" ]; then
    touch "$1"
fi
echo $2 > $1
# echo "file $1 contains $(cat $1)"

