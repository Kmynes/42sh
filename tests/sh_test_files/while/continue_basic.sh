i=1
while [ i -le 10 ]
do
    (( i++ ))
    if [ i -gt 6 ]
    then
        continue
    fi
    echo $i
done