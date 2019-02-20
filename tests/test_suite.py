import yaml
import subprocess
import os
import sys

def run(mycode_output):
    """ Runs a command in shell, returns stdout and stderror """
    return subprocess.run(mycode_output, shell=True, stdout=subprocess.PIPE,
                          stderr=subprocess.PIPE)

def output_diff(title, ref_output, mycode_output):
    """ Diff between reference output and mycode output, prints results.
    returns 0 on success and 1 on failure"""
    # print the name of the test without a newline
    print(title + ": ", end='')
    # check if there was a difference in standard out or standard err, but 
    # make sure you don't say "OK" when there is no stderr
    if ref_output.stdout == mycode_output.stdout \
        or (ref_output.stderr == mycode_output.stderr \
        and ref_output.stderr != b''):
        # if there is no difference between both outputs, print OK in green
        print("\033[1;32;40m OK \033[m")
        return 0
    # otherwise, print KO in red
    print("\033[1;31;40m KO", end='')
    if mycode_output.stderr != b'':
        print(" - error occurred \033[m")
    else:
        print(" - unexpected output \033[m")
    return 1

def category_list():
    """ This function prints a list of all test categories """
    directory = os.path.dirname(os.path.abspath(__file__))
    print(directory)
    for category in os.listdir(directory):
        if not (os.path.isfile(directory+"/"+category) or category == "unit"):
            print(category)
       
"""
def category_list():
    for category in os.listdir('.'):
        # only go check in folders whose name isn't "unit"
        if not (os.path.isfile(category) or category == "unit"):
            print(category)
"""

def full_test_suite():
    total_tests = total_fails = 0
    directory = os.path.dirname(os.path.abspath(__file__))

    for category in os.listdir(directory):
        category_tests = category_fails = 0
        # only go check in folders whose name isn't "unit"
        if not (os.path.isfile(directory+"/"+category) or category == "unit"):
            # print category title
            print("\n=============== " + category + " ===============\n")
            # for every test file in that category
            for test_file in os.listdir(directory+"/"+category):
                category_tests += 1
                # open file
                with open((directory+"/"+category+"/"+test_file), "r") as file:
                    # load info from yaml
                    test = yaml.load(file)
                # run reference test
                ref_output = run(test["ref"])
                # run program test
                mycode_output = run(test["mycode"])
                # run diff
                category_fails += output_diff(test_file, ref_output, mycode_output)

            print("In the " + str(category) + " category there were " \
                + str(category_tests) + " tests including " + str(category_fails) \
                + " failure(s).")
            total_tests += category_tests
            total_fails += category_fails

    print("\nThere were " + str(total_tests) + " tests total, of which " \
        + str(total_fails) + " were failures.")

def argument_manager():
    if len(sys.argv) == 1:
        full_test_suite()
        return 0
    if sys.argv[1] == "--list" or sys.argv[1] == "-l":
        category_list()
        return 0

    else:
        print("Unknown command")
        return 1

argument_manager()