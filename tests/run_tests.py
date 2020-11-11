import os
from argparse import ArgumentParser
import subprocess

def run_test_suite(tsuite_name, tcase):
    cwd = os.getcwd()
    if "None" == tcase:
        command = "cd " + cwd +"; python3 -u -m robot -A profiles/profile.txt -r " + tsuite_name + "_report.html -l " + tsuite_name+ "_log.html -o " + tsuite_name + "_output.xml tests/"+ tsuite_name +".robot; exec bash"
    else:
        command = "cd " + cwd +"; python3 -u -m robot -A profiles/profile.txt -r " + tsuite_name + "_report.html -l " + tsuite_name+ "_log.html -o " + tsuite_name + "_output.xml -t \""+ tcase+"\" tests/"+ tsuite_name +".robot; exec bash" 
    
    print(command)

    subprocess.Popen(['gnome-terminal', '--', 'bash', '-c', command])

if __name__ == '__main__':
    # Menu
    parser = ArgumentParser()
    parser.add_argument('-ts', '--testsuite', type=str, default="tests_mpls.robot",
                        help="Path for tests folder")
    parser.add_argument('-tc', '--testcase', type=str, default="None",
                        help="Path for tests folder")
    args= parser.parse_args()
    args=vars(args)
    run_test_suite(args["testsuite"], args["testcase"])