#!/bin/bash

let count=0;
for f in $(ls ./Tests2/*.txt); do 
	./a.out <$f > ./Tests2/`basename $f .txt`.output; 
done;

for f in $(ls ./Tests2/*.output); do
	diff -Bw $f  ./Tests2/`basename $f .output`.txt.expected > ./Tests2/`basename $f .output`.diff;
done

for f in $(ls Tests2/*.diff); do
	echo "========================================================";
	echo "FILE:" `basename $f .output`;
	echo "========================================================";
	if [ -s $f ]; then
		cat ./Tests2/`basename $f .diff`.txt;
		echo "--------------------------------------------------------";
		cat $f
	else
		count=$((count+1));
		echo "NO ERRORS HERE!";
	fi
done

echo $count;

rm Tests2/*.output
rm Tests2/*.diff

