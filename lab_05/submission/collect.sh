#!/bin/bash
# Run on Linux as an ordinary user. All experiments use a new temporary folder.
set -u
if [ "$(uname -s)" != Linux ] || [ "$(id -u)" -eq 0 ]; then
    echo 'Run this script on Linux as a non-root user.' >&2
    exit 1
fi
work=$(mktemp -d "${TMPDIR:-/tmp}/os-lab5.XXXXXX")
trap 'chmod -R u+rwX "$work"; rm -rf "$work"' EXIT
cd "$work" || exit 1
export LC_ALL=C
run() { printf '\n$ %s\n' "$*"; bash -c "$*"; }
run 'whoami; pwd'
run 'ls /; ls -ld /etc /etc/passwd /bin /dev/null /tmp'
run 'ls -l /dev | head; file /usr/bin/ls /etc/passwd /bin'
run 'du -sh /var/log 2>/dev/null; du -sh /usr 2>/dev/null'
run 'echo hello > notes.txt; stat notes.txt; ls -li notes.txt'
run 'ln notes.txt hard.txt; ls -li notes.txt hard.txt; rm notes.txt; cat hard.txt; ls -li hard.txt'
run 'ln -s hard.txt soft.txt; ls -li hard.txt soft.txt; cat soft.txt; rm hard.txt; cat soft.txt; ls -l soft.txt'
run 'mkdir d; ls -ld d; mkdir d/x d/y; ls -ld d'
run 'echo x > one.txt; ls -l one.txt; du -h one.txt; truncate -s 1G big.img; ls -lh big.img; du -h big.img; rm big.img'
run 'echo secret > s.txt; chmod 600 s.txt; ls -l s.txt; chmod 000 s.txt; cat s.txt; chmod u+r s.txt; cat s.txt'
run 'umask; touch new.txt; mkdir newdir; ls -ld new.txt newdir'
run 'mkdir box; echo hi > box/f; chmod u=r,go= box; ls box; cat box/f'
run 'chmod u=x,go= box; ls box; cat box/f; chmod 755 box'
run 'ls -l /usr/bin/passwd; ls -ld /tmp; cat /etc/shadow; ls -l /etc/shadow'
run 'lsblk; df -h; mount | grep " / "'
run 'grep -c processor /proc/cpuinfo; head -3 /proc/meminfo; head -5 /proc/self/status; ls -l /proc/self/fd'
run 'gzip -c /etc/passwd > notes.txt; file notes.txt; xxd notes.txt | head -1'
run 'echo retained-data > bigfile; exec 3< bigfile; rm bigfile; ls -l /proc/$$/fd/3; cat <&3; exec 3<&-'
