for (( a = 1; a < 100; a++ ))
do
./a.out $a 100 > test/$a.txt
done

for (( a = 1, b = 2; a < 99; a++, b++ ))
do
diff test/$a.txt test/$b.txt
done