#!/bin/bash
mitsuba "${1}" &
echo "${1} - Début du traitement" > log.txt
((i = 0))
while pgrep mitsuba>/dev/null
	do
		date >> log.txt
		if  [ $i -gt 0 ]
			then killall -HUP mitsuba
		fi
		sleep 5
		if [ -f ${1//.*}.exr ];
			then mv ${1//.*}.exr ${1//.*}_${i}.exr
		fi
		top -n 1 -b | grep mitsuba >> log.txt
		sleep 55
		((i++))
done
