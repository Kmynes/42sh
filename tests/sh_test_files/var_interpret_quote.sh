dir_test='tests'
dir_sh_test='sh_test_files'
printer='printer.py'

path="${dir_test}/${dir_sh_test}/${printer}"

suffix='team'
part1='My name is'
part2='BlueShell 42'
phrase="${part1} $part2 ${suffix}"

python3 "${path}" $phrase