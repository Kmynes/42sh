import ctypes

def run_unit_test():

    test_42sh = ctypes.CDLL("/root/work/42sh/build/libtest_42sh.so")
    return test_42sh.test_unit()

run_unit_test()