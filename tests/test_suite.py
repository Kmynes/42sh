import yaml
import subprocess
import os

def run(mycode):
    ''' Runs a command in shell, returns stdout and stderror'''
    return subprocess.run(mycode, shell=True, stdout=subprocess.PIPE,
                          stderr=subprocess.PIPE)

def test_check(ref_output, mycode_output)
    ''' Checks for differences between reference output and mycode output '''


for category in os.listdir('.'):
    # only go check in folders whose name isn't "unit"
    if not (os.path.isfile(category) or category == "unit"):
        # print category title
        print("=============== " + category + " ===============\n")s
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
                test_check(ref_output, mycode_output)
