import os
import sys
import parse
import error
import check
import subprocess

try:
    with open("src/main.pf", "r") as f:
        contents = f.read()
        f.close()
except:
    error.error("Could not open src/main.pf")
    sys.exit(1)

try:
    output = parse.Parser(contents+"\n\n").parse()
except:
    error.error("Could not compile: Syntax error")
    sys.exit(1)

try:
    include = "./include/"
    with open("target/main.cpp", 'w') as f:
        f.write(
"""
#include <iostream>
#include "../include/function.cpp"
#include "../include/io.cpp"
#include "../include/error.cpp"
#include "../include/data.cpp"
#include "../include/logic.cpp"
using namespace std;\n\n\n
""" + output + """


int main(int argc, char** argv) {
    Pair args;
    if (argc > 1) {
        args = Pair().call(String(argv[argc-1]), None());
        for (int i = argc-2; i > 0; --i) {
            args = Pair().call(String(argv[i]), args);
        }
    } else {
        args = Pair().call(None(), None());
    }

    Main().call(args);
    return 0;
}""")
        f.close()
except:
    error.error("Could not write to target/main.cpp, has the ./target directoy been moved?")
    sys.exit(1)



# try:
#     # process = Popen(
#     #     args="g++ --std=c++14 target/main.cpp -o target/bin",
#     #     shell=True
#     # )
#     process = subprocess.Popen(
#         "g++ --std=c++14 target/main.cpp -o target/bin".split(),
#         stdout=subprocess.PIPE,
#         stderr=subprocess.PIPE
#     )

#     (out, err) = process.communicate()
#     if err:
#         print("Error:", str(err, "unicode"))
#     # print("program error:", err)
# except:
#     error.error("Error during compilation. Did you typecheck your code?")
# process = Popen(
#     args="g++ --std=c++14 target/main.cpp -o target/bin",
#     shell=True
# )
process = subprocess.Popen(
    "g++ --std=c++14 target/main.cpp -o target/bin".split(),
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE
)

(out, err) = process.communicate()

check.check(err)