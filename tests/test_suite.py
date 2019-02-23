import subprocess
import os
import sys
try:
    import yaml
except ImportError: 
    print("YAML is not installed on this machine")


def run(mycode, flag="", flag_value=""):
    """ Runs a command in shell, returns stdout and stderror """
    if not flag:
        return subprocess.run(mycode, shell=True,
                              stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if flag == "timer":
        print("--Timed")
        return subprocess.run(mycode, shell=True,
                              stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if flag == "sanitise":
        print("--Sanitised")
        return subprocess.run(mycode, shell=True, 
                              stdout=subprocess.PIPE, stderr=subprocess.PIPE)

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
    number_of_categories = 0
    directory = os.path.dirname(os.path.abspath(__file__))
    for category in os.listdir(directory):
        if not (os.path.isfile(directory+"/"+category) or category == "unit"):
            number_of_categories+=1
            print(category)
    print(str(number_of_categories)+" categories were succesfully printed.")
       

def full_test_suite(arguments=[None]*3):
    """ Launches a full test suite """
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
                test_name = test_file.replace(".yml", "")
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
                category_fails += output_diff(test_name, ref_output, mycode_output)

            print("In the " + str(category) + " category there were " \
                + str(category_tests) + " tests including " + str(category_fails) \
                + " failure(s).")
            total_tests += category_tests
            total_fails += category_fails

    print("\nThere were " + str(total_tests) + " tests total, of which " \
        + str(total_fails) + " were failures.")


def category_test(arguments):
    """ test suite for a single category given in argument """
    category_fails = category_tests = 0
    directory = os.path.dirname(os.path.abspath(__file__))
    for test_file in os.listdir(directory+"/"+arguments[0]):
        test_name = test_file.replace(".yml", "")
        category_tests += 1
        # open file
        with open((directory+"/"+arguments[0]+"/"+test_file), "r") as file:
            # load info from yaml
            test = yaml.load(file)
        # run reference test
        ref_output = run(test["ref"])
        # run program test
        mycode_output = run(test["mycode"])
        # run diff
        category_fails += output_diff(test_name, ref_output, mycode_output)
    print("In the " + str(arguments[0]) + " category there were " \
        + str(category_tests) + " tests including " + str(category_fails) \
        + " failure(s).")


def argument_parser():
    """ parses command line arguments, returns error code """
    if len(sys.argv) == 1:
        full_test_suite()
        return [0]
    check_value = argument_checker()
    if check_value[0]:
        return check_value
    if "--list" in sys.argv or "-l" in sys.argv:
        if len(sys.argv) > 2:
            return [5]
        category_list()
        return [0]
    if len(sys.argv) > 6:
        return [1]
    # arguments list: [category, sanity, timer]
    arguments = [None]*3
    if "-c" in sys.argv or "--category" in sys.argv:
        if "-c" in sys.argv:
            arguments[0] = sys.argv[sys.argv.index("-c")+1]
        else:
            arguments[0] = sys.argv[sys.argv.index("--category")+1]
    if "-s" in sys.argv or "--sane" in sys.argv:
        arguments[1] = "sanitised"
    if "-t" in sys.argv or "--timer" in sys.argv:
        if "-t" in sys.argv:
            arguments[2] = sys.argv[sys.argv.index("-t")+1]
        else:
            arguments[2] = sys.argv[sys.argv.index("--timer")+1]
    exit_code = argument_manager(arguments)
    return exit_code

def argument_checker():
    """ checks arguments given in command line to see if they are supported.
    returns error code """
    supported_arguments = ["-c", "--category", "-l", "--list", "-t",
                       "--timer", "-s", "--sane"]
    for argument in sys.argv[1:len(sys.argv)]:
        previous_argument = sys.argv[sys.argv.index(argument)-1]
        if previous_argument == "-t" or previous_argument == "--timer":
            try:
                int(argument)
            except ValueError:
                return [4, argument]
        if previous_argument != "-c" and previous_argument != "--category" \
            and previous_argument != "-t" and previous_argument != "--timer":
            if argument not in supported_arguments:
                return [3, argument]
    return [0]


def argument_manager(arguments):
    """ manages what to do after argument list is obtained,
    returns error code """
    if arguments[0]:
        try:
            category_test(arguments)
        except FileNotFoundError:
            return [2, arguments[0]]
    else:
        full_test_suite(arguments)
    return [0]

def error_code_display(error_code):
    if error_code[0] == 1:
        print("Invalid number of arguments: " + str(len(sys.argv)))
    if error_code[0] == 2:
        print("File not found (category does not exist): '" \
              + str(error_code[1]) + "'")
    if error_code[0] == 3:
        print("Invalid argument: '" + str(error_code[1])+"'")
    if error_code[0] == 4:
        print("Value Error. Timer flag expects an integer and was given: '"
              + str(error_code[1]) + "'")
    if error_code[0] == 5:
        print("Invalid number of arguments: !" + str(len(sys.argv)))
        print("When list flag is active, no other arguments are accepted.")


# main function
exit_code = argument_parser()
if exit_code[0]:
    error_code_display(exit_code)
quit(exit_code[0])