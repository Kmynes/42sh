import ctypes
import sys

def run_unit_test(path):
    test_42sh = ctypes.CDLL(path + "libtest_42sh.so")
    return test_42sh.test_unit()

if __name__ == "__main__":
    status = run_unit_test("")
    sys.exit(status)