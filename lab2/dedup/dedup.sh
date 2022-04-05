# TODO: Write your shell script (for question 7) in this file.
#!/bin/bash
cd $1
size=`find -name "*.csv" | sort | wc -l | cut -d ' ' -f 1`
find -name "*.csv" | sort | tr "\n" " " > file.txt
while read f; do
echo "$f"
done <file.txt
cat file.txt