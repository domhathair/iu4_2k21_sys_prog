#!/bin/bash
FAIL_LOGIN=$(cat /var/log/auth.log | grep "sshd" | tail -n 2 | grep "Failed password for")
SUCC_LOGIN=$(last | head -n 5 | grep "pts/0" | head -n 1)
HOUR_NOW=$(date +%H)
MIN_NOW=$(date -u +%M)
SEC_NOW=$(date -u +%S)
echo "Current time: $HOUR_NOW:$MIN_NOW"
SUB="still logged in"
#echo "$SUCC_LOGIN"
#echo "$FAIL_LOGIN"
NUM_FAIL_LOGIN=$(cat /var/log/auth.log | grep "sshd" | grep "Failed password for" | wc -l)
IP_ADDRESS=$(echo $FAIL_LOGIN | sed -n 's/.*from \(.*\) port.*/\1/p')
#echo $IP_ADDRESS

if [[ "$SUCC_LOGIN" == *"$SUB"* ]]
then
	HOUR_CURR=$(echo $SUCC_LOGIN | cut -b 36,37 | sed 's/^0*//')
	MIN_CURR=$(echo $SUCC_LOGIN | cut -b 39,40 | sed 's/^0*//')
	echo "Current session started: $HOUR_CURR:$MIN_CURR"
	HOUR_PASS=$(( (($HOUR_NOW * 60 + $MIN_NOW) - ($HOUR_CURR * 60 + $MIN_CURR)) / 60 ))
	MIN_PASS=$(( (($HOUR_NOW * 60 + $MIN_NOW) - ($HOUR_CURR * 60 + $MIN_CURR)) % 60 ))
	#echo "$HOUR_PASS"
	#echo "$MIN_PASS"
	if [ "$HOUR_PASS" -gt "0" ]
	then
		echo "Sessions lasts: $HOUR_PASS hour(s) and $MIN_PASS minute(s)"
	else
		echo "Sessions lasts: $MIN_PASS minute(s)"
	fi
elif [ "$NUM_FAIL_LOGIN" -ge 3 ]
	then
FIRST_CONNECTION=$(cat /var/log/auth.log | grep "sshd" | grep "Failed password for" | tail -n 3 | head -n 1)
SECOND_CONNECTION=$(cat /var/log/auth.log | grep "sshd" | grep "Failed password for" | tail -n 2 | head -n 1 )
THIRD_CONNECTION=$(cat /var/log/auth.log | grep "sshd" | grep "Failed password for" | tail -n 1)
#echo $FIRST_CONNECTION
#echo $SECOND_CONNECTION
#echo $THIRD_CONNECTION

MIN_FIRST=$(echo $FIRST_CONNECTION | cut -b 11,12 | sed 's/^0*//')
if [ "$MIN_FIRST" == '' ]
then
MIN_FIRST=0
fi
#echo $MIN_FIRST
SEC_FIRST=$(echo $FIRST_CONNECTION | cut -b 14,15 | sed 's/^0*//')
if [ "$SEC_FIRST" == '' ]
then
SEC_FIRST=0
fi
echo "First login time: $MIN_FIRST:$SEC_FIRST"
MIN_SECOND=$(echo $SECOND_CONNECTION | cut -b 11,12 | sed 's/^0*//')
if [ "$MIN_SECOND" == '' ]
then
MIN_SECOND=0
fi
#echo $MIN_SECOND
SEC_SECOND=$(echo $SECOND_CONNECTION | cut -b 14,15 | sed 's/^0*//')
if [ "$SEC_SECOND" == '' ]
then
SEC_SECOND=0
fi
echo "Second login time: $MIN_SECOND:$SEC_SECOND"
MIN_THIRD=$(echo $THIRD_CONNECTION | cut -b 11,12 | sed 's/^0*//')
if [ "$MIN_THIRD" == '' ]
then
MIN_THIRD=0
fi
#echo $MIN_THIRD
SEC_THIRD=$(echo $THIRD_CONNECTION | cut -b 14,15 | sed 's/^0*//')
if [ "$SEC_THIRD" == '' ]
then
SEC_THIRD=0
fi
echo "Third login time: $MIN_THIRD:$SEC_THIRD"

if [ "$MIN_FIRST" = 59 ] && [ "$SEC_SECOND" -le "$SEC_SECOND" ]
	then
	TIMEOUT1=$(( 60 * $MIN_SECOND + 60 - $SEC_FIRST + $SEC_SECOND ))
else
	if [ "$MIN_SECOND" -lt "$MIN_FIRST" ]
		then
		TIMEOUT1=60
	else
		TIMEOUT1=$(( ($MIN_SECOND - $MIN_FIRST) * 60 - $SEC_FIRST + $SEC_SECOND ))
	fi
fi

if [ "$MIN_SECOND" = 59 ] && [ "$SEC_THIRD" -le "$SEC_SECOND" ]
	then
	TIMEOUT2=$(( 60 * $MIN_THIRD + 60 - $SEC_SECOND + $SEC_THIRD ))
else
	if [ "$MIN_THIRD" -lt "$MIN_SECOND" ]
		then
		TIMEOUT2=60
	else
		TIMEOUT2=$(( ($MIN_THIRD - $MIN_SECOND) * 60 - $SEC_SECOND + $SEC_THIRD ))
	fi
fi

if [ "$MIN_THIRD" = 59 ] && [ "$SEC_NOW" -le "$SEC_THIRD" ]
	then
	TIMEOUT_LOCK=$(( 60 * $MIN_NOW + 60 - $SEC_THIRD + $SEC_NOW ))
else
	if [ "$MIN_NOW" -lt "$MIN_THIRD" ]
		then
		TIMEOUT_LOCK=300
	else
		TIMEOUT_LOCK=$(( ($MIN_NOW - $MIN_THIRD) * 60 - $SEC_THIRD + $SEC_NOW ))
	fi
fi

if [ "$TIMEOUT1" -le 60 ] && [ "$TIMEOUT2" -le 60 ] && [ "$TIMEOUT_LOCK" -le 300 ]
	then
		iptables -A INPUT -s $IP_ADDRESS -j DROP
		echo "Activate lock"
	else
		STILL_LOCKED=$(iptables -L | grep ".22")
		#echo "Locked: $STILL_LOCKED"
		if [ "$STILL_LOCKED" != '' ]
			then
			iptables -D INPUT -s $IP_ADDRESS -j DROP
			echo "Deactivate lock"
		else
			echo "Lock already deactivated"
		fi
fi

#echo $FIRST_CONNECTION
#echo $SECOND_CONNECTION
#echo $THIRD_CONNECTION
#echo $TIMEOUT1
#echo $TIMEOUT2
#echo $TIMEOUT_LOCK
else
echo "There are no active connections"
fi
#echo $IP_ADDRESS
