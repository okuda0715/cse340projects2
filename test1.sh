#!/bin/bash

let count=0;
for f in $(ls ./testsGrading/*.txt); do 
	./a.out <$f > ./testsGrading/`basename $f .txt`.output; 
done;

for f in $(ls ./testsGrading/*.output); do
	diff -Bw $f  ./testsGrading/`basename $f .output`.txt.expected > ./testsGrading/`basename $f .output`.diff;
done

for f in $(ls testsGrading/*.diff); do
	echo "========================================================";
	echo "FILE:" `basename $f .output`;
	echo "========================================================";
	if [ -s $f ]; then
		cat ./testsGrading/`basename $f .diff`.txt;
		echo "--------------------------------------------------------";
		cat $f
	else
		count=$((count+1));
		echo "NO ERRORS HERE!";
	fi
done

echo $count;

rm testsGrading/*.output
rm testsGrading/*.diff

