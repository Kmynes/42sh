dir_test='../tests'
dir_sh_test='sh_test_files'
printer_file='printer.py'

path_printer="${dir_test}/${dir_sh_test}/${printer_file}"

suffix='team'
part1='My name is'
part2='BlueShell 42'
phrase="${part1} $part2 ${suffix}"

python3 $path_printer $phrase

prog='python3'

$prog --version

$prog $path_printer $phrase

$prog $path_printer "empty variable [$empty]"