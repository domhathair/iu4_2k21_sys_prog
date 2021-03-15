#!/bin/bash
Cur_date=$(date +%d)
echo "Today is Oct $Cur_date"
echo "Mathes:" && sudo cat /var/log/auth.log | grep "session opened for user domhathair" \
| grep -c "Oct $Cur_date"


