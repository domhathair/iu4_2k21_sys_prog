#!/bin/bash
if [ -z "$1" ]
	then
		echo "No parameter 1"
	else
	if [ -e "$1" ] && ! [ -z "$2" ]
		then
		mkdir -p -m=764 $2
		NOW_DATE=$(date -u +%d)
		tar -cvzf $2/file$NOW_DATE.gz $1
		NUM_FILES=$(ls -1t $2 | wc -l)
		echo "Date: $NOW_DATE"
		echo "№ of files: $NUM_FILES"
		if [ $NUM_FILES -gt 7 ]
			then
			FILE_NAME=$(ls -1t $2 | sed -n 8p)
			echo $FILE_NAME
			rm $2/$FILE_NAME
		fi
	else
		echo "No such parameter"
	fi
fi
