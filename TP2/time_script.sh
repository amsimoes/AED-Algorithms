#! /bin/bash

counter=50000
counter2=0
while [ $counter -le 1000000 ]; do
	echo "$counter" >> "tempos$1.txt"
	counter2=0
	while [ $counter2 -lt 15 ]; do
		./$1 $counter >> "tempos$1.txt"
		let counter2=counter2+1
	done
	let counter=counter+50000
	echo "" >> "tempos$1.txt"
done

echo "DONE :-)"
