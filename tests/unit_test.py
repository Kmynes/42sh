import ctypes
import sys
from os import path

SHARED_LIB_PATH = "{}/build/{}".format(path.dirname(path.dirname(
    path.abspath(__file__))),
                                       "libtest_42sh.so")


def run_unit_test():
    print(SHARED_LIB_PATH)
    test_42sh = ctypes.CDLL(SHARED_LIB_PATH)
    return test_42sh.test_unit()


if __name__ == "__main__":
    status = run_unit_test()
    sys.exit(status)
