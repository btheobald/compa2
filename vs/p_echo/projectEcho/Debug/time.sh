START=$(date +%s.%N)
./projectEcho.exe
END=$(date +%s.%N)
DIFF=$(echo "$END - $START")
echo $DIFF