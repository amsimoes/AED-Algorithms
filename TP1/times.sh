#! /bin/bash

step=50
media=0

while [ $step -le 500 ]; do
	echo "$step" >> "tempos$1.txt"
	media=0
	while [ $media -lt 15 ]; do
		./$1 $step 1 >> "tempos$1.txt"
		let media=media+1
	done
	let step=step+50
	echo "" >> "tempos$1.txt"
done

step=500

while [ $step -le 10000 ]; do
	echo "$step" >> "tempos$1.txt"
	media=0
	while [ $media -lt 15 ]; do
		./$1 $step 1 >> "tempos$1.txt"
		let media=media+1
	done
	let step=step+500
	echo "" >> "tempos$1.txt"
done

step=50000

while [ $step -le 100000 ]; do
	echo "$step" >> "tempos$1.txt"
	media=0
	while [ $media -lt 15 ]; do
		./$1 $step 1 >> "tempos$1.txt"
		let media=media+1
	done
	let step=step+50000
	echo "" >> "tempos$1.txt"
done

echo "DONE :-)"