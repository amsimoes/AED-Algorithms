#! /bin/bash

counter=0
counter2=0
while [ $counter -le 10000 ]; do
	echo "$counter" >> "tempos_pequenos_$1.txt"
	counter2=0
	while [ $counter2 -lt 10 ]; do
		./$1 $counter >> "tempos_pequenos_$1.txt"
		let counter2=counter2+1
	done
	let counter=counter+500
	echo "" >> "tempos_pequenos_$1.txt"
done

echo "DONE :-)"