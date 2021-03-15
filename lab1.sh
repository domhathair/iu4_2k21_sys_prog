#!/bin/bash
CURRENT_USER=$(whoami)
if [ "$2" = '' ] && [ -d $2 ]
	then
	echo "No file, bro"
else
	SUB='/'
	if [[ "$2" == *"$SUB"* ]]
		then
		echo "You can not create directories, users, etc. Type only name of the file"
	else
		echo "Name: $0"
		echo "Paremeter: $1"
		echo "File: $2"
		if [ $1 = "-c" ] || [ $1 = "-d" ]
			then
			if [ $1 = "-c" ]
				then
				FILE_NAME=$(basename $2)
				SIMILAR_FILE=$(pwd $2 | ls -1 | grep -w $FILE_NAME)
				if [ "$SIMILAR_FILE" = '' ]
					then
					touch $2
					chmod 764 $2
					echo "File created"
				else
					echo "Found similar file $SIMILAR_FILE. Please rename it"
				fi
			else

				if [ -e $2 ]
					then
					ACCESS=$(ls -l $2 | grep -w $CURRENT_USER)
					CHANGE=$(ls -l $2 | cut -c9)
					if [ "$ACCESS" = '' ] && [ "$CHANGE" = w ] || [ "$ACCESS" != '' ]
						then
						rm $2
						echo "File deleted"
					else
						echo "Something went wrong again"
					fi
				else
					echo "There is no file $2 available"
				fi
			fi
		else
			echo "Unknown parameter $1, use -c to create or -d to delete files"
		fi
	fi
fi

