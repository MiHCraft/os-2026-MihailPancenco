#!/bin/bash
# Usage: ./report.sh access.log

if [ "$#" -ne 1 ]; then
    echo "usage: $0 <logfile>" >&2
    exit 1
fi

log=$1
if [ ! -f "$log" ]; then
    echo "no such file: $log" >&2
    exit 1
fi

total=$(wc -l < "$log")
fails=$(grep -c ' FAIL ' "$log")
printf '%s requests, %s failed\n' "$total" "$fails"

for u in user0 user1 user2 user3 user4 user5 user6; do
    n=$(grep -c " $u FAIL " "$log")
    printf '%s: %s failures\n' "$u" "$n"
done