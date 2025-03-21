#!/bin/bash

if [ -n "$1" ]
then
	fl=1
	echo "------------------ONLY RESIDUAL AND TIME------------------"
else
	fl=0
	echo "-----------------------ALL RESULTS------------------------"
fi
	
dir="small_tests"

data_s4="\
a.txt \
a20.txt \
b.txt \
"

data_s6="\
c.txt \
d.txt \
e.txt \
f.txt \
"

for data in ${data_s4}
do \
	data_file="${dir}/${data}"
	echo "====================== ${data_file} ======================"
	result=`./a.out 4 4 4 0 ${data_file} | tr -d '\0'`\
	
	if [ $fl -eq 1 ]
	then
		error=`echo "${result}" | grep -a 'ERROR'`
		residual=`echo "${result}" | grep -a 'Residual'`
		time=`echo "${result}" | grep -a 'Time'`
		echo "${error}"
		echo "${residual}"
		echo "${time}"
	else
		echo "${result}"
	fi
	echo "------------------------------------------------------------"
done

for data in ${data_s6}
do \
	data_file="${dir}/${data}"
	echo "====================== ${data_file} ======================"
	result=`./a.out 6 6 6 0 ${data_file} | tr -d '\0'`\
	
	if [ $fl -eq 1 ]
	then
		error=`echo "${result}" | grep -a 'ERROR'`
		residual=`echo "${result}" | grep -a 'Residual'`
		time=`echo "${result}" | grep -a 'Time'`
		echo "${error}"
		echo "${residual}"
		echo "${time}"
	else
		echo "${result}"
	fi
	echo "------------------------------------------------------------"
done


for (( s = 1; s <= 4; s++ ))
do \
	for (( n = 1; n <= 30; n++ ))
	do \
		if [ "$s" -ne 4 ] || [ "$n" -le 15 ];
		then
			for (( m = 3; m <= 30; m+=3 ))
			do \
				if [ "$m" -le "$n" ]
				then
					echo "================= n = ${n} m = ${m} s = ${s} ================= "
					result=`./a.out ${n} ${m} 4 ${s}| tr -d '\0'`\
					
					if [ $fl -eq 1 ]
					then	
						error=`echo "${result}" | grep -a 'ERROR'`
						residual=`echo "${result}" | grep -a 'Residual'`
						time=`echo "${result}" | grep -a 'Time'`
						echo "${error}"
						echo "${residual}"
						echo "${time}"

					else
						echo "${result}"
					fi
				fi
			done
		fi
	done
done







