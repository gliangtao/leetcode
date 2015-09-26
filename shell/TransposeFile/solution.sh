#!/bin/bash

function work1 ## OOM
{
let num=`tail -1 file.txt |awk '{ print NF }'`
let i=1

MY_AWK=`which awk`
while (($i <= $num)); do
CMD="$MY_AWK '{ print \$$i }' < file.txt"
echo `sh -c "$CMD"`
let i=$i+1
done
}

function work2
{
awk '
{
    if (NR != 1) {
        for (i = 1; i <= NF; i++) {
            s[i] = s[i] " " $i;
        }
    } else {
        for (i = 1; i <= NF; i++) {
            s[i] = $i;
        }
    }
}
END {
    for (i = 1; s[i] != ""; i++) {
        print s[i];
    }
}' file.txt
}

work2
