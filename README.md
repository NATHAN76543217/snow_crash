# snow_crash
Security project of 42school


Link to the VM: https://projects.intra.42.fr/uploads/document/document/5137/SnowCrash.iso.


## Level00

find interesting files: `find / -user flag00`.
file with `cdiiddwpgswtgt` founded.
Supposed to be a `Caesar Cipher`. Use [Dcode](https://www.dcode.fr/caesar-cipher).
Password is: `nottoohardhere`.
Flag is: `x24ti5gi3x0ol2eh4esiuxias`

# level01
find interesting files: `find / -user flag01`.
Nothing founded, let's check in `/etc/passwd`.
Found:
`flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash`.

Password is: `42hDRfypTqqnw`.
