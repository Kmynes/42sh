path='tests/sh_test_files'
empty_file="${path}/empty_file"
printer="${path_file}/printer.py"

if cat $empty_file then
    python3 $printer "le Fichier ${path_file} à pû être afficher"
fi