import sys

val=""
for i in range(1, len(sys.argv)):
    val += sys.argv[i] + " "

print(val)