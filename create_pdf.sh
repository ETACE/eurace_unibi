#!/bin/bash
#Read list of files and convert from C to PS and to PDF

BASE=$PWD
#Directory list
#FOLDER_LIST=$(find -type d)
#echo $FOLDER_LIST

#Leaf Directory list
#FOLDER_LIST=$(find . -type d | sort | awk '$0 !~ last {print last} {last=$0} END {print last}')

export FOLDER_LIST=$(ls -A --group-directories-first)
echo $FOLDER_LIST


#Step 2a: Prepare bash file
rm create.sh
echo -n "pdftk " >> create.sh

#Step 2: add all PDF paths
for folder in $FOLDER_LIST; do
	echo "Cat $folder/out.pdf to create.sh"
	echo -n "$folder/out.pdf" >> create.sh
	echo -n " " >> create.sh
done

#Step 2c: add output file
echo -n " cat output Full_code.pdf"  >> create.sh

#Step 3: Source create.sh
bash create.sh

