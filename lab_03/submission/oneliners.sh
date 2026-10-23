#!/bin/bash
# Run from ~/os-lab3: bash oneliners.sh

# Q1. How many requests failed?
printf '\nQ1 - failed requests:\n'; grep -c ' FAIL ' access.log

# Q2. How many different pages were requested, and which?
printf '\nQ2 - distinct pages:\n'; pages=$(cut -d' ' -f5 access.log | sort -u); printf '%s\n' "$pages"; printf 'Distinct pages: %s\n' "$(printf '%s\n' "$pages" | wc -l)"

# Q3. How many requests did each page get?
printf '\nQ3 - requests per page:\n'; cut -d' ' -f5 access.log | sort | uniq -c

# Q4. Which user or users have the most failed requests, and how many?
printf '\nQ4 - users with most failures:\n'; grep ' FAIL ' access.log | cut -d' ' -f3 | sort | uniq -c | sort -rn | awk 'NR == 1 {highest = $1} $1 == highest {print $2 ": " $1 " failures"}'

# Q5. How many requests did user3 make, and how many failed?
printf '\nQ5 - user3:\n'; printf 'user3: %s total, %s failed\n' "$(grep -c ' user3 ' access.log)" "$(grep -c ' user3 FAIL ' access.log)"

# Q6. Print the last three failed requests, showing only time and user.
printf '\nQ6 - last three failures:\n'; grep ' FAIL ' access.log | tail -3 | cut -d' ' -f2,3

# Q7. Which login shells occur in /etc/passwd, and how many accounts use each?
printf '\nQ7 - login shells on this machine:\n'; cut -d: -f7 /etc/passwd | sort | uniq -c | sort -rn

# Q8. Compare the number of lines from ls /etc and ls -l /etc.
printf '\nQ8 - ls output line counts:\n'; printf 'ls /etc: '; ls /etc | wc -l; printf 'ls -l /etc: '; ls -l /etc | wc -l

# Bonus (+1). Failed requests whose minute ends in 0.
printf '\nBONUS - failed requests at minutes ending in 0:\n'; grep -E '10:[0-5]0 [^ ]+ FAIL ' access.log | wc -l