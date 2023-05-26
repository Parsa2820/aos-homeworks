gcc -o write write.c
gcc -o read read.c
gcc -o c c.c
gcc -o c-direct c-direct.c

echo "Running write"
./write

echo "Running cache drop and read"
sync; echo 3 > /proc/sys/vm/drop_caches
./read

rm -f file.txt

echo "Running write again"
./write

echo "Running read without cache drop"
./read

rm -f file.txt

echo "Running part c without direct"
./c

echo "Running part c with direct"
./c-direct