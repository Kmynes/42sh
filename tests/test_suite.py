import subprocess
import yaml


def run(mycode):
    ''' Runs a command in shell, returns stdout and stderror'''
    return subprocess.run(mycode, shell=True, stdout=subprocess.PIPE,
                          stderr=subprocess.PIPE)


for category in ".":
    print(category)
    for testFile in "./category":
        # this loads the info from testFile into the test variable
        with open(testFile, "r") as file:
            test = yaml.load(file)

            for test, data in test.items():
                # run reference test
                ref = run(data["ref"])

                # run actual code
                mycode = run(data["mycode"])

                # Listing of errors that occured
                errors = []
                if ref.stdout != mycode.stdout:
                    errors.append("STDOUT")
                if ref.stderr != mycode.stderr:
                    errors.append("STDERR")
                #if ref.returncode != mycode.returncode:
                #   errors.append("RETURN CODE")

                res = ", ".join(errors) if errors else "OK"
                print("-" * 80)
                print("{id}: {desc} [{res}]".format(id=test, desc=data["desc"], res=res))

                # decode() convertit des bytes en str

                expected = ref.stdout.decode()
                if not expected:
                    expected = ref.stderr.decode()
                returned = mycode.stdout.decode()
                if not returned:
                    returned = mycode.stderr.decode()
                print("\t", "EXPECTED: \n" + expected)
                print("\t", "RETURNED: \n" + returned)