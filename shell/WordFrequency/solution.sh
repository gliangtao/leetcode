#!/bin/bash
# Read from the file words.txt and output the word frequency list to stdout.
tr -cs "[:alpha:]" "\n" <words.txt |sort -d | uniq -c |sort -nr | awk '{ print $2, $1 }'
