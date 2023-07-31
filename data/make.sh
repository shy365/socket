#!/bin/bash
file="/home/fuhao/project/A.txt"

> "$file"

for((i=100;i<=999;i++))
do
	echo "$i" >> "$file"
done

	echo "写入完成"
