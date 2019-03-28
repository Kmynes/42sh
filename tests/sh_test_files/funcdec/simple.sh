function func_test (       ) {
    echo $1
    echo $2
    echo $3
    echo $4
    echo $5
}

func_test 'test1' 'test2' 'test3' 'test4' 'test5'

func2 () (
    echo 'Just an other test'
)
func2

func3     (){
    echo 'And why not ?'
}


    func3
function global () {
    echo 'Global call -----'
     func2
     func3
}
global