path='../tests/sh_test_files'
prg="python3 ${path}"
prg_err="$prg/error.py"
prg_suc="$prg/succes.py"
printer="$prg/printer.py"

if $prg_err then $printer 'error' fi
if $prg_suc then $printer 'success' fi