#!/bin/sh -e

# if the number of arguments is not 2, print usage and exit
if [ $# -ne 2 ]; then
    echo "Usage: $0 <filesdir> <searchstr>"
    exit 1

# If the directory does not exist, print error and exit
elif [ ! -d "$1" ]; then
    echo "Error: Directory $1 does not exist."
    exit 1
fi

# rename the variables for readability
filesdir=$1
searchstr=$2

# search for any objects that are files (type f) in the filesdir provided, and 
# print the filename, then count the number of lines(filenames) printed with wc -l
echo "The number of files are $(find $filesdir/ -name "*.*" -type f -print | wc -l) "

# search for the string recuring in the filesdir provided, and print the
# filename, then count the number of lines(filenames) printed with wc -l
echo "and the number of matching lines are $( grep -r $searchstr $filesdir/* | wc -l)"
