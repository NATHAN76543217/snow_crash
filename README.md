# snow_crash
Security project of 42school


Link to the VM: https://projects.intra.42.fr/uploads/document/document/5137/SnowCrash.iso.


## Level00

Find interesting files: `find / -user flag00`.
File conraining `cdiiddwpgswtgt` founded.
Supposed to be a `Caesar Cipher`. Use [Dcode](https://www.dcode.fr/caesar-cipher).
Password is: `nottoohardhere`.
Flag is: `x24ti5gi3x0ol2eh4esiuxias`

## level01
Find interesting files: `find / -user flag01`.
Nothing founded, let's check in `/etc/passwd`.
Found:
`flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash`.
Put this onto a user.txt file and give it to `John`.
John output:
`flag01:abcdefg:3001:3001::/home/flag/flag01:/bin/bash`.    

Password is: `abcdefg`.
Flag is: `f2av5il02puano7naaf6adaaf`.

## level02

There is a `level02.pcap` file. a `.pcap` file can be opened with `wireshark` and represent a capture of some network transmissions.     
First we need to extract this file using `scp`.
`scp -q -P 2222 level02@10.64.1.226:./level02.pcap ./level02/`

Then I open the file with Wireshark, select the first packet and `Follow the TCP stream`.
Now I can see the password in plain text: `Password: ft_wandr...NDRel.L0L`.
Then I need to interpret the DEL characters and the remaining password is: `ft_waNDReL0L`.