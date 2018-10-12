#!/bin/bash
set -x

cp sample sample.abs
./abs2rel sample.abs sample.rel

function zip {
	/usr/bin/zip $1.zip $1
}

function hffzip {
	/opt/local/bin/hffzip -c -i $1 -o $1.hff
}

for cmd in compress gzip zip hffzip; do
	echo "Testing $cmd"
	rm sample.abs_$cmd* sample.rel_$cmd*
	cp sample.abs sample.abs_$cmd
	cp sample.rel sample.rel_$cmd
	$cmd sample.abs_$cmd
	$cmd sample.rel_$cmd
done
ls -latr sample.*
