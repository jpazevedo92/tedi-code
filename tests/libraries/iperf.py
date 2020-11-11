import os
import signal
import uavssh
import json
import HTML
import threading
import subprocess
import time
from queue import Queue
from argparse import ArgumentParser
from robot.libraries.BuiltIn import BuiltIn

def start_udp_test_server(port="5001", output_file_name="T4", repetition="1"):
    cwd = os.getcwd()
    command = "stdbuf -o 0 iperf3 -s -p "+ port +" 2>&1 | tee "+ cwd + "/logs/server_"+ output_file_name +".txt; "
    subprocess.Popen(['gnome-terminal', '--', 'bash', '-c', command], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

def start_multiple_udp_test_server(num_servers, output_file_name="T4"):
    cwd = os.getcwd()
    for i in range(0, int(num_servers)):
        id_server = i + 1
        port = 5000 + id_server
        command = "stdbuf -o 0 iperf3 -s -p "+ str(port) +" 2>&1 | tee "+ cwd + "/logs/server_" + output_file_name + "_" + str(id_server) +".txt;"
        subprocess.Popen(['gnome-terminal', '--', 'bash', '-c', command], stdout=subprocess.PIPE, stderr=subprocess.PIPE)


def simple_udp_test(client_ip, base_ip, port="5001", interval="1", test_time="30", bitrate="100m" ,json_output="yes", output_file_name="T4",repetitions="10" ):
    ssh_client = uavssh.SSH(client_ip, "pi", "raspberry")
    command = "iperf3 -c "+ base_ip + " -u -p "+ port + " -i "+ interval +" -t"+ test_time +" -b" + bitrate
    table_data = []
    header_row = ['ID', 'Transfer (MB)', 'Bitrate(Mb/s)', 'Jitter(ms)', 'Loss(%)']
    if "yes" == json_output:
        command = command + " -J"
    for i in range(0, int(repetitions)):    
        log_file = ssh_client.exec_cmd(command, output_file_name, str(i))
        result = parse_results(log_file, i+1)
        BuiltIn().log_to_console(result)
        table_data.append(result)
    htmlcode = HTML.table(table_data, header_row=header_row)
    BuiltIn().set_test_message("*HTML*" + htmlcode , "yes")
    stop_udp_test_server(port)

def thread_udp_test(thread_id, client_ip, base_ip, interval="1", test_time="30", bitrate="100m" ,json_output="yes", output_file_name="T4",repetitions="10" ):
    ssh_client = uavssh.SSH(client_ip, "pi", "raspberry")
    port = 5000 + thread_id
    command = "iperf3 -c "+ base_ip + " -u -p "+ str(port) + " -i "+ interval +" -t"+ test_time +" -b" + bitrate
    table_data = []
    header_row = ['ID', 'Transfer (MB)', 'Bitrate (Mb/s)', 'Jitter (ms)', 'Loss (%)']
    if "yes" == json_output:
        command = command + " -J"
    for i in range(0, int(repetitions)):
        log_file = ssh_client.exec_cmd(command, output_file_name, str(i+1))
        result = parse_results(log_file, i+1)
        BuiltIn().log_to_console(result)
        table_data.append(result)
    htmlcode = HTML.table(table_data, header_row=header_row)
    BuiltIn().set_test_message("*HTML*" + htmlcode , "yes")
    stop_udp_test_server(port)

def multiple_udp_test(num_clients, client1_ip, client2_ip, client3_ip="None", base_ip="10.0.10.1", interval="1", test_time="30", bitrate="100m" ,json_output="yes", output_file_name="T4",repetitions="10"):
    threads = list()
    for i in range(0, int(num_clients)):
        index = i + 1
        thread_name = "thread"+str(index)
        thread_file_name = output_file_name + "_" + "thread"+str(index)
        if 1 == index:
            x = threading.Thread(target=thread_udp_test, args=(index, client1_ip, base_ip, 
                                                               interval, test_time, bitrate, 
                                                               json_output, thread_file_name, repetitions, ))
        if 2 == index:
            x = threading.Thread(target=thread_udp_test, args=(index, client2_ip, base_ip, 
                                                               interval, test_time, bitrate, 
                                                               json_output, thread_file_name, repetitions, ))
        if 3 == index:
            x = threading.Thread(target=thread_udp_test, args=(index, client3_ip, base_ip, 
                                                               interval, test_time, bitrate, 
                                                               json_output, thread_file_name, repetitions, ))
        threads.append(x)
        x.start()
    
    for thread in threads:
        thread.join()

def parse_results(json_file,  id=0, udp_results="yes"):
    with open(json_file) as json_file:
        data = json.load(json_file)
        result = data['end']['sum']
        bytes_transfered = round(result['bytes']*0.00000095367432, 2)
        bitrate = round(result['bits_per_second']/1000000, 2)
        jitter = round(result['jitter_ms'], 5)
        lost_percent = round(result['lost_percent'], 3)
        results = [id, bytes_transfered, bitrate, jitter, str(lost_percent)]
    return results

def stop_udp_test_server(port="5001"):
    p=subprocess.Popen(['fuser', str(port)+"/tcp"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = p.communicate()
    pid = int(stdout.decode("utf-8").strip(" "))
    os.kill(pid, signal.SIGTERM)

def stop_multiple_udp_test_server(num_servers):
    for i in range(0, int(num_servers)):
        id_server = i + 1
        port = 5000 + id_server
        p=subprocess.Popen(['fuser', str(port)+"/tcp"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = p.communicate()
        pid = int(stdout.decode("utf-8").strip(" "))
        os.kill(pid, signal.SIGTERM)

    