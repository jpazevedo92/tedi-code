import os
import paramiko
from paramiko import SSHClient
from robot.libraries.BuiltIn import BuiltIn
from argparse import ArgumentParser

class SSH:
    def __init__(self, hname, uname, passw):
        self.ssh = SSHClient()
        self.ssh.load_system_host_keys()
        self.ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.ssh.connect(hostname=hname, username=uname, password=passw)

    def exec_cmd(self, cmd, output_file_name="T4", repetition="1", json_output="yes"):
        cwd = os.getcwd()
        stdin, stdout, stderr = self.ssh.exec_command(cmd, get_pty=True)
        if "yes" == json_output:
                log_file = cwd + "/logs/client_"+ output_file_name + "_" + repetition + ".json"
        else:
            log_file = cwd + "/logs/client_"+ output_file_name + "_" + repetition + ".txt"

        with open(log_file, 'w') as f:
            for line in iter(stdout.readline, ""):
                f.write(line)
                print(line, end="")
        if stderr.channel.recv_exit_status() != 0:
            print(stderr.read())
        else:
            print(stdout.read())
        
        return log_file

if __name__ == '__main__':
    # Menu
    parser = ArgumentParser()
    parser.add_argument('-H', '--hostname', type=str, default="10.0.10.2",
                        help="Hostname")
    parser.add_argument('-u', '--username', type=str, default="pi",
                        help="Username")
    parser.add_argument('-p', '--password', type=str, default="raspberry",
                    help="Password")

    args= parser.parse_args()
    args=vars(args)
    ssh = SSH(args["hostname"], args["username"], args["password"])
    ssh.exec_cmd("ls")

