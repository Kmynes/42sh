dir_test='../tests'
dir_sh_test='sh_test_files'

path_printer="${dir_test}/${dir_sh_test}/${printer_file}"

suffix='team'
part1='My name is'
part2='BlueShell 42'
phrase="${part1} $part2 ${suffix}"

echo $phrase

prog='python3'

$prog --version

echo $phrase

echo "empty variable [$empty]"

echo "an other empty variable [${empty_var}]"

word='BLUE'

echo "print just a little [$word]"