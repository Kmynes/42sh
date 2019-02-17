import yaml
import subprocess
import os

def run(mycode_output):
    ''' Runs a command in shell, returns stdout and stderror '''
    return subprocess.run(mycode_output, shell=True, stdout=subprocess.PIPE,
                          stderr=subprocess.PIPE)

def test_check(title, ref_output, mycode_output):
    ''' Diff between reference output and mycode output, prints results '''
    print(title + ": ", end='')

    # check if there was a difference in standard out or standard err, but 
    # make sure you don't say "OK" when there is no stderr
    if ref_output.stdout == mycode_output.stdout \
        or (ref_output.stderr == mycode_output.stderr \
        and ref_output.stderr != b''):
        print("\033[1;32;40m OK \033[m")

    else:
        print("\033[1;31;40m KO \033[m")


for category in os.listdir('.'):
    # only go check in folders whose name isn't "unit"
    if not (os.path.isfile(category) or category == "unit"):
        # print category title
        print("=============== " + category + " ===============\n")
        # for every test file in that category
        for test_file in os.listdir(category):
            # open file
            with open((category+"/"+test_file), "r") as file:
                # load info from yaml
                test = yaml.load(file)
                # run reference test
                ref_output = run(test["ref"])
                # run program test
                mycode_output = run(test["mycode"])
                # run diff
                test_check(test["name"], ref_output, mycode_output)