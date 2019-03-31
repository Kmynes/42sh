import subprocess
from coding_style_checker import file_selector
import os
import sys
from test_unit import run_unit_test
try:
    import yaml
except ImportError: 
    print("YAML is not installed on this machine")
    quit(2)

##
# \file test_suite.py
# \brief Main test suite body.
#
# The main test suite body. It parses test suite arguments and then outputs
# the results in a clean format. This test suite only deals with integration
# tests, as unit tests are managed independently by the cmake.
# That being said, the test suite still has support for all the options 
# and flags.
# \author Daniel
# \version v0.5
# \date March 2019
# \description
def run(test, mode="other", arguments=[None]*4):
    """ Runs a command in shell, returns stdout and stderror """
    # arguments list: [category, sanity, timer]
    file_directory = os.path.dirname(os.path.abspath(__file__))
    build_directory = file_directory.replace("tests", "build")
    if mode == "ref":
        test = "bash --posix "+test
    if mode == "42sh":
        test = "./42sh "+test
    if arguments[1]:
        test = "valgrind "+test
    if arguments[2]:
        try:
            return subprocess.run(test, shell=True, cwd=build_directory,
                              stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                             timeout=int(arguments[2]))
        except:
            return "timeout"
    return subprocess.run(test, shell=True, cwd=build_directory,
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
    ref_return = int(ref_output.returncode)
    ref_stdout = str(ref_output.stdout)
    ref_stderr = str(ref_output.stderr)
    mycode_return = int(mycode_output.returncode)
    mycode_stdout = str(mycode_output.stdout)
    mycode_stderr = str(mycode_output.stderr)
    # valgrind checks
    if arguments[1]:
        if valgrind_error_extractor(mycode_stderr) > 0:
            print("\033[1;31;40m KO", end='')
            print(" - valgrind error \033[m")
            if arguments[3]:
                print_debug(ref_stdout, ref_stderr, mycode_stdout, mycode_stderr, "err")
            return 1
        mycode_stderr = valgrind_cleanup(mycode_stderr)
    # and ref_stderr == mycode_stderr <= temporarily removing error output check
    if ref_stdout == mycode_stdout and ref_return == mycode_return:
        if arguments[3]:
            print_debug(ref_stdout, ref_stderr, mycode_stdout, mycode_stderr, type)
        # if there is no difference between both outputs, print OK in green
        print("\033[1;32;40m OK \033[m")
        return 0
    # otherwise, print KO in red
    print("\033[91m KO", end='')
    # temporarily removing error output print.
    #if mycode_stderr != "b''":
    #    print(" - unexpected error \033[m")
    #    if arguments[3]:
    #        print_debug(ref_stdout, ref_stderr, mycode_stdout,
    #                    mycode_stderr, "err")
    if ref_return is not mycode_return:
        print(" - Expected return: "+str(ref_return)+", but got:"+str(mycode_return)+".")
        if arguments[3]:
            print_debug(ref_stdout, ref_stderr, mycode_stdout, mycode_stderr, "err")

    else:
        print(" - unexpected output \033[m")
        if arguments[3]:
            print_debug(ref_stdout, ref_stderr, mycode_stdout,
                        mycode_stderr, "out")
    return 1

def print_debug(ref_stdout, ref_stderr, mycode_stdout, mycode_stderr, type):
    """ prints debug information """
    ref_stderr = ref_stderr[2:len(ref_stderr)-1]
    mycode_stderr = mycode_stderr[2:len(mycode_stderr)-1]
    ref_stdout = ref_stdout[2:len(ref_stdout)-1]
    mycode_stdout = mycode_stdout[2:len(mycode_stdout)-1]
    if type == "err":
        if ref_stderr == "":
            print(" "*8+"There was no error output for ref."\
               +" Printing stdout instead...")
            print(" "*8 + "\033[93m"+"ref stdout: \033[m")
            print(" "*12 + ref_stdout)
        else:
            print(" "*8 + "\033[93m"+"ref stderr: \033[m")
            print(" "*12 + ref_stderr)
        print(" "*8 + "\033[93m"+"42sh stderr: \033[m")
        print(" "*12 + mycode_stderr)
    if type == "out":
        if ref_stdout == "":
            print(" "*8+"There was no standard output for ref."\
               +" Printing stderr instead...")
            print(" "*8 + "\033[93m"+"ref stderr: \033[m")
            print(" "*12 + ref_stderr)
        else:
            print(" "*8 + "\033[93m"+"ref stdout: \033[m")
            print(" "*12 + ref_stdout)
        print(" "*8 + "\033[93m"+"42sh stdout: \033[m")
        print(" "*12 + mycode_stdout)
    return

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
    directory = os.path.dirname(os.path.abspath(__file__))+"/integration"
    for category in os.listdir(directory):
        if not os.path.isfile(directory+"/"+category):
            number_of_categories+=1
            print(category)
    print(str(number_of_categories)+" categories were succesfully printed.")


def full_test_suite(arguments=[None]*4):
    """ Executes a full test suite """
    total_tests = total_fails = 0
    print("= unit tests " + "="*67)
    total_fails += run_unit_test()
    print()
    directory = os.path.dirname(os.path.abspath(__file__))+"/integration"

    for category in os.listdir(directory):
        if not os.path.isfile(directory+"/"+category):
            # print category title
            arguments[0] = category
            [category_tests, category_fails] = category_test(arguments)

            total_tests += category_tests
            total_fails += category_fails

    print("\nThere were " + str(total_tests) + " tests total, of which " \
        + str(total_fails) + " were failures.")
    if (total_fails):
        return [1]
    else:
        return [0]

def category_test(arguments):
    """ Executes tests for a specific category given in argument """
    category = arguments[0]
    if category == "unit":
        print("= unit tests " + "="*67)
        fails = run_unit_test()
        print()
        if fails > 0:
            return [0, 1]
        else:
            return [0, 0]
    print("= "+category+" "+"="*(77-len(category)))
    category_fails = category_tests = 0
    directory = os.path.dirname(os.path.abspath(__file__))+"/integration"
    for test_file in os.listdir(directory+"/"+category):
        test_name = test_file.replace(".yml", "")
        category_tests += 1
        # open file
        with open((directory+"/"+arguments[0]+"/"+test_file), "r") as file:
            # load info from yaml
            test = yaml.load(file)
        custom_timer = False
        # if timer mode is enabled:
        if arguments[2] is not None:
            try:
                str(test["timer"])
                custom_timer = True
                if arguments[3]:
                    print("Custom timer applied: " + str(test["timer"]))
            except:
                pass

        # run reference test
        ref_output = run(test["test"], "ref")
        # run program test
        if custom_timer:
            mycode_output = run(test["test"], "42sh", [arguments[0], arguments[1], str(test["timer"]), arguments])
        else:
            mycode_output = run(test["test"], "42sh", arguments)
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

def helper():
    """ Prints a list of all available commands """
    print("" \
          + "-l or --list \n" \
          + "    Lists all categories\n" \
          + "-s or --sanity \n" \
          + "    Runs tests with Valgrind.\n" \
          + "    Tests will fail if Valgrind returns errors.\n" \
          + "-d or --debug \n" \
          + "    Runs tests in debug mode.\n" \
          + "    Prints out plenty of information on each test,\n" \
          + "    including error outputs for each test.\n" \
          + "-t <int> or --timeout <int> \n" \
          + "    Adds a timeout (in seconds) to the test executions.\n" \
          + "    Tests will fail if time runs out.\n" \
          + "-c <category_name> or --category <category_name> \n" \
          + "    Executes tests for specified category.\n" \
          + "--style \n" \
          + "    Tests coding style. \n")

def argument_parser():
    """ parses command line arguments, returns error code """
    if len(sys.argv) == 1:
        fails = full_test_suite()
        return fails
    check_value = argument_checker()
    if check_value[0]:
        return check_value
    if "-l" in sys.argv or "--list" in sys.argv:
        if len(sys.argv) > 2:
            return [5, "list"]
        category_list()
        return [0]
    if "-h" in sys.argv or "--help" in sys.argv:
        if len(sys.argv) > 2:
            return [5, "help"]
        helper()
        return [0]
    if "--style" in sys.argv:
        if len(sys.argv) > 2:
            return [5, "help"]
        file_selector()
        return [0]
    if len(sys.argv) > 7:
        return [8]
    # arguments list: [category, sanity, timer, debug]
    arguments = [None]*4
    if "-c" in sys.argv or "--category" in sys.argv:
        if "-c" in sys.argv:
            arguments[0] = sys.argv[sys.argv.index("-c")+1]
        else:
            arguments[0] = sys.argv[sys.argv.index("--category")+1]
    if "-s" in sys.argv or "--sanity" in sys.argv:
        arguments[1] = "sanitised"
    if "-d" in sys.argv or "--debug" in sys.argv:
        arguments[3] = True
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
    supported_arguments = ["-c", "--category",  "-t", "--timer", "--style",
                           "-s", "--sanity", "-l", "--list", "-h", "--help"
                           "-d", "--debug"]
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
        print("\033[93m- running in timed mode \033[m")
    if arguments[1]:
        print("\033[93m- running in sanitised mode \033[m")
    if arguments[3]:
        print("\033[93m- running in debug mode \033[m")
    if arguments[0]:
        try:
            [tests, fails] = category_test(arguments)
            if fails > 0:
                return [1]
            else:
                return [0]
        except FileNotFoundError:
            return [2, arguments[0]]
    fails = full_test_suite(arguments)
    if fails[0]:
        return [1]
    else:
        return [0]

def error_code_display(error_code):
    """ displays proper error message based on error code given """
    
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
        print("When " + error_code[1] + " flag is active, no other arguments" \
              + " are accepted.")
    if error_code[0] == 6:
        print("Missing argument after '" + error_code[1] + "'")
    if error_code[0] == 7:
        print("Expected argument after '" + error_code[1] + "',"
              + " but instead got flag")
    if error_code[0] == 8:
        print("Invalid number of arguments: '" + str(len(sys.argv)) + "'")

def check_if_made():
    """ Checks if the code has been built, if it hasn't, warns the user """
    file_directory = os.path.dirname(os.path.abspath(__file__))
    build_directory = file_directory.replace("tests", "build")
    if not os.path.isdir(build_directory):
        print("Could not access executable, did you run make?")
        quit(2)

def clean_cache():
    """ Cleans the pycache generated by python """
    #print("Cleaning cache...", end = "")
    file_directory = os.path.dirname(os.path.abspath(__file__))
    subprocess.run("rm -r __pycache__", shell=True, cwd=file_directory)
    #print("...done")

# main function
def main():
    """ Main function that calls the others. mostly manages exit scenarios. """

    check_if_made()
    exit_code = argument_parser()
    clean_cache()
    if exit_code[0] > 1:
        error_code_display(exit_code)
        quit(2)
    if exit_code[0]:
        quit(1)
    else:
        quit(0)

main()