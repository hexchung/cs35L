#!/bin/bash
D=$1
result1=$(ls -a $D)
declare -a ARRAY
let i=0
old_IFS=$IFS
IFS=$(echo -en "\n\t")
for FILE1 in $result1
do
	nospaces=$(echo "$FILE1" | sed 's/ /_/g')
	if [ "$nospaces" != "$FILE1" ]
	then
		$(mv "$D/$FILE1" "$D/$nospaces")
	fi
done
result=$(ls -a $D)
for FILE in $result
do
	if [ ! -L "$D/$FILE" ]
	then	
		if [ -f "$D/$FILE" ]
		then
			if $(echo "$FILE" | grep -q '[^A-Za-z0-9._\/]')
			then
				newfile=$(echo "$FILE" | sed 's/[^A-Za-z0-9._\/]/_/g')
                $(mv "$D/$FILE" "$D/$newfile")
				ARRAY[$i]="$D/$newfile"
			else
				ARRAY[$i]="$D/$FILE"
			fi
		let i=i+1
		fi
	fi
done
for j in "${ARRAY[@]}"
do
	if [ ! -r "$j" ]
	then
		echo "the file: $j is not readable and will not be treated as a duplicate."
	fi
done

for m in "${!ARRAY[@]}"
do
	for n in "${!ARRAY[@]}"
	do
		if $(cmp -s "${ARRAY[$m]}" "${ARRAY[$n]}")
		then
			if [ "$m" != "$n" ]
			then
				file1="${ARRAY[$m]}"
				file2="${ARRAY[$n]}"

				if [ $(echo $file1 | grep -q '^.') ] || [ "$file1" \< "$file2" ] 
				then
                    			$(ln $file1 tmp ; mv tmp $file2)
				else
					$(ln $file2 tmp ; mv tmp $file1)
				fi
			fi
		fi
	done
done
IFS=${old_IFS}
