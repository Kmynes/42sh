i=1
j=1
while [ i -le 10 ]
do
    while [ j -le 3 ]
    do
        echo $j
        (( j++ ))
    done
    echo $i
    (( i++ ))
done