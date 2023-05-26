gcc -o write write.c
gcc -o read read.c

echo "Running write without buffer cache"
./write NOBUFFERCACHE

echo "Running read without buffer cache"
./read NOBUFFERCACHE

rm -f *.txt

echo "Running write with buffer cache"
./write BUFFERCACHE

echo "Running read with buffer cache"
./read BUFFERCACHE

rm -f *.txt
