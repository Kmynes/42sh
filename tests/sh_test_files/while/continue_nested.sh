i=1
j=1
while [ i -le 10 ]
do
    while [ j -le 3 ]
    do
        (( j++ ))
        if [ i -gt 6 ]
        then
            continue 2
        fi
        echo $j
    done
    (( i++ ))
    echo $i
done