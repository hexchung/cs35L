#!/bin/bash 
cat /dev/stdin | grep -o '<td>.*</td>' | sed 's/<[^>]*>//g' | sed 's/,/\n/g' | sed 's/^\s//g' | sed 's/\s/\n/g' | tr -s '\n' | tr '`' "'" | tr '[:upper:]' '[:lower:]' | sed "/[^pk\'mnwlhaeiou]/d" | sort -u
