path='tmp_directori'
mkdir -p $path

for number_file in 1 2 3 4 5
do
    echo "$path/"
    #touch "$path/$number_file"
done

rm -r $path