path='../tests/sh_test_files'
prg="python3 ${path}"
prg_err="$prg/error.py"
prg_suc="$prg/succes.py"

if $prg_err; then echo 'error'; fi
if $prg_suc; then echo 'success'; fi