#! /bin/bash

counter=50
counter2=0
while [ $counter -le 500 ]; do
	echo "$counter" >> "tempos_pequenoss_$1.txt"
	counter2=0
	while [ $counter2 -lt 15 ]; do
		./$1 $counter 1 >> "tempos_pequenoss_$1.txt"
		let counter2=counter2+1
	done
	let counter=counter+50
	echo "" >> "tempos_pequenoss_$1.txt"
done

echo "DONE :-)"