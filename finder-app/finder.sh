#!/bin/bash -e


if [ $# -ne 2 ]; then
    echo "Usage: $0 <filesdir> <searchstr>"
    exit 1
elif [ ! -d "$1" ]; then
    echo "Error: Directory $1 does not exist."
    exit 1
fi


filesdir=$1
searchstr=$2

echo "The number of files are $(find $filesdir/ -name "*.*" -type f -print | wc -l) "
echo "and the number of matching lines are $( grep -r $searchstr $filesdir/* | wc -l)"
