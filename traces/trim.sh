#!/bin/sh

for f in *.out;
do
    ext="${f##*.}"
    path="${f%.*}"
    out="${path}-trim.${ext}"
    sed '1,26000d' $f > $out
done