import subprocess
import os
import sys
try:
    import yaml
except ImportError: 
    print("YAML is not installed on this machine")
    quit()


def run(code, arguments=[None]*3):
    """ Runs a command in shell, returns stdout and stderror """
    # arguments list: [category, sanity, timer]
    if arguments[1]:
        code = "valgrind "+code
    if arguments[2]:
        print("--Timed")
        try:
            return subprocess.run(code, shell=True,
                              stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                             timeout=int(arguments[2]))
        except:
            return "timeout"
    return subprocess.run(code, shell=True,
                          stdout=subprocess.PIPE, stderr=subprocess.PIPE)

def output_diff(test_name, ref_output, mycode_output, arguments):
    """ Diff between reference output and mycode output, prints results.
    returns 0 on success and 1 on failure"""
    print("    "+test_name + ": ", end='')
    
    if arguments[2]:
        if "timeout" in str(mycode_output):
            print("\033[1;31;40m KO", end='')
            print(" - timed out \033[m")
            return 1
    ref_stdout = str(ref_output.stdout)
    ref_stderr = str(ref_output.stderr)
    mycode_stdout = str(mycode_output.stdout)
    mycode_stderr = str(mycode_output.stderr)
    # valgrind checks
    if arguments[1]:
        if valgrind_error_extractor(mycode_stderr) > 0:
            print("\033[1;31;40m KO", end='')
            print(" - valgrind error \033[m")
            return 1
        mycode_stderr = valgrind_cleanup(mycode_stderr)
        
    if ref_stdout == mycode_stdout \
        or (ref_stderr == mycode_stderr \
        and ref_stderr != "b''"):
        # if there is no difference between both outputs, print OK in green
        print("\033[1;32;40m OK \033[m")
        return 0
    # otherwise, print KO in red
    print("\033[1;31;40m KO", end='')
    if mycode_stderr != "b''":
        print(" - unexpected error \033[m")
    else:
        print(" - unexpected output \033[m")
    return 1

def valgrind_cleanup(stderr):
    """ Cleans stderr by removing valgrind output """
    if "Memcheck" in stderr:
        cleaned_stderr = "b''"
    else:
        cleaned_stderr = stderr.replace("valgrind: ", "")
    return cleaned_stderr


def valgrind_error_extractor(stderr):
    """ Extracts number of errors received from valgrind when sanitised """
    if stderr.find("ERROR SUMMARY:") == -1:
        return 0
    err_number_start = stderr.find("ERROR SUMMARY:")+15
    err_number_end = stderr.find("errors from", err_number_start,
                                err_number_start+30)-1
    number_of_errors = int(stderr[err_number_start:err_number_end])
    return number_of_errors

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
        # only go check in folders whose name isn't "unit"
        if not (os.path.isfile(directory+"/"+category) or category == "unit"):
            # print category title
            print("= "+category+" "+"="*(77-len(category)))
            arguments[0] = category
            [category_tests, category_fails] = category_test(arguments)

            total_tests += category_tests
            total_fails += category_fails

    print("\nThere were " + str(total_tests) + " tests total, of which " \
        + str(total_fails) + " were failures.")


def category_test(arguments):
    """ test suite for a single category given in argument """
    category = arguments[0]
    category_fails = category_tests = 0
    directory = os.path.dirname(os.path.abspath(__file__))
    for test_file in os.listdir(directory+"/"+category):
        test_name = test_file.replace(".yml", "")
        category_tests += 1
        # open file
        with open((directory+"/"+arguments[0]+"/"+test_file), "r") as file:
            # load info from yaml
            test = yaml.load(file)
        # run reference test
        ref_output = run(test["ref"])
        # run program test
        mycode_output = run(test["mycode"], arguments)
        # run diff
        category_fails += output_diff(test_name, ref_output, mycode_output,
                                     arguments)
    category_end_print(category_tests, category_fails, category)
    return [category_tests, category_fails]

def category_end_print(category_tests, category_fails, test_name):
    """ prints category summary message """
    print("In the " + str(test_name) + " category there were " \
        + str(category_tests) + " tests including " + str(category_fails) \
        + " failure(s). \n")

def argument_parser():
    """ parses command line arguments, returns error code """
    if len(sys.argv) == 1:
        full_test_suite()
        return [0]
    check_value = argument_checker()
    if check_value[0]:
        return check_value
    if "-l" in sys.argv or "--list" in sys.argv:
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
    if "-s" in sys.argv or "--sanity" in sys.argv:
        arguments[1] = "sanitised"
    if "-t" in sys.argv or "--timeout" in sys.argv:
        if "-t" in sys.argv:
            arguments[2] = sys.argv[sys.argv.index("-t")+1]
        else:
            arguments[2] = sys.argv[sys.argv.index("--timeout")+1]
    exit_code = argument_manager(arguments)
    return exit_code

def argument_checker():
    """ checks arguments given in command line to see if they are supported.
    returns error code """
    supported_arguments = ["-c", "--category",  "-t", "--timer",
                           "-s", "--sanity", "-l", "--list"]
    for argument in sys.argv[1:len(sys.argv)]:
        previous_argument = sys.argv[sys.argv.index(argument)-1]
        if previous_argument == "-t" or previous_argument == "--timeout":
            try:
                int(argument)
            except ValueError:
                return [4, argument]
        if previous_argument not in supported_arguments[0:3]:
            if argument not in supported_arguments: 
                return [3, argument]
        if argument in supported_arguments[0:3]:
            if sys.argv.index(argument) == len(sys.argv)-1:
                return [6, argument]
            if sys.argv[sys.argv.index(argument)+1] in supported_arguments:
                return [7, argument]
    return [0]


def argument_manager(arguments):
    """ manages what to do after argument list is obtained,
    returns error code """
    if arguments[2]:
        print("- running in timed mode")
    if arguments[1]:
        print("- running in sanitised mode")
    if arguments[0]:
        try:
            category_test(arguments)
        except FileNotFoundError:
            return [2, arguments[0]]
    else:
        full_test_suite(arguments)
    return [0]

def error_code_display(error_code):
    """ displays proper error message based on error code given """
    if error_code[0] == 1:
        print("Invalid number of arguments: '" + str(len(sys.argv)) + "'")
    if error_code[0] == 2:
        print("File not found (category does not exist): '" \
              + str(error_code[1]) + "'")
    if error_code[0] == 3:
        print("Invalid argument: '" + str(error_code[1])+"'")
    if error_code[0] == 4:
        print("Value Error. Timer flag expects an integer and was given: '"
              + str(error_code[1]) + "'")
    if error_code[0] == 5:
        print("Invalid number of arguments: '" + str(len(sys.argv)) + "'")
        print("When list flag is active, no other arguments are accepted.")
    if error_code[0] == 6:
        print("Missing argument after '" + error_code[1] + "'")
    if error_code[0] == 7:
        print("Expected argument after '" + error_code[1] + "',"
              + " but instead got flag")

# main function
exit_code = argument_parser()
if exit_code[0]:
    error_code_display(exit_code)
quit(exit_code[0])