for (( a = 1; a < 27; a++ ))
do
echo $a
./a.out $a 27 1.txt > test/$a.txt
done

for (( a = 1, b = 2; a < 27; a++, b++ ))
do
diff test/$a.txt test/$b.txt
done