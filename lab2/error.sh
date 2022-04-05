grep -i error /var/log/syslog | head -1 | cut -d ' ' -f 1-3 >oldtime
grep -i error /var/log/syslog | tail -1 | cut -d ' ' -f 1-4 >latesttime
grep -o -i error /var/log/syslog | wc -l >count
d1="$oldtime"
d2="$latesttime"
c="$count"
date1=$(date -d "$d1" +%s) 
date2=$(date -d "$d2" +%s)
diff=`expr $date1 - $date2`
echo `expr $diff/$c`
rm oldtime latesttime count