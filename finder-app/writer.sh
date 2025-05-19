#!/bin/bash -e

# If the number of arguments is not 2, print usage and exit
if [ $# -ne 2 ]; then
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

# get the path of the file without the filename
path=$(dirname "$1")
# if the path does not exist, create it
if [ ! -e "$path" ]; then
    mkdir -p "$path" 
fi

# if the file does not exist, create it
if [ ! -f "$1" ]; then
    touch "$1"
fi
# write the string to the file (overwriting any existing content)
echo $2 > $1

