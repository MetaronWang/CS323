import os
import sys

if len(sys.argv) > 1:
    path = sys.argv[1]
    name = path[:len(path)-4]
    if os.path.exists(path):
        os.system("./splc "+path+" >"+name+".out")
    else:
        print("File not exist")
else:
    while True:
        path = input("Please input the path of SPL code: ")
        name = path[:len(path)-4]
        if os.path.exists(path):
            os.system("./splc < "+path+" >"+name+".out")
        else:
            print("File not exist")
