import os
import subprocess
import shlex
import json
import ipaddress
import socket
import logging
import logging.handlers as handlers
import time
import re

from logging.handlers import TimedRotatingFileHandler
from datetime import datetime
from tkinter import *


app_scripts_dir = os.path.abspath(os.path.join(__file__,"..","scripts"))
app_settings_dir = os.path.abspath(os.path.join(__file__,"..","settings"))

class Application:    
    def __init__(self, master=None):
        self.command_msg = StringVar()
        self.fonte = ("Verdana", "8")
        self.container1 = Frame(master)
        self.container1["pady"] = 10
        self.container1.pack()

        self.title = Label(self.container1, text="UAVConfig")
        self.title["font"] = ("Calibri", "9", "bold")
        self.title.pack ()

        self.container2 = Frame(master)
        self.container2["padx"] = 20
        self.container2["pady"] = 5
        self.container2.pack()

        self.lbltun = Label(self.container2, 
        text="Create Tunnel:", font=self.fonte, width=15)
        self.lbltun.pack(side=LEFT)

        self.tun_in = Entry(self.container2, font=self.fonte, width=5)
        self.tun_in.pack(side=LEFT)

        self.lbldir = Label(self.container2, 
        text="=>", font=self.fonte, width=2)
        self.lbldir.pack(side=LEFT)

        self.tun_out = Entry(self.container2, font=self.fonte, width=5)
        self.tun_out.pack(side=LEFT)

        self.start_tun = Button(self.container2, text="Create", 
        font=self.fonte, width=10)
        self.start_tun["command"] = self._start_tun
        self.start_tun.pack(side=RIGHT)

        self.container3 = Frame(master)
        self.container3["padx"] = 20
        self.container3["pady"] = 5
        self.container3.pack()

        self.lbltun = Label(self.container3, 
        text="Tunnel Name:", font=self.fonte, width=15)
        self.lbltun.pack(side=LEFT)

        self.tun_name = Entry(self.container3, font=self.fonte, width=10)
        self.tun_name.pack(side=LEFT)

    
        self.exit_frame = Frame(master)
        self.exit_frame["padx"] = 20
        self.exit_frame["pady"] = 5
        self.exit_frame.pack(side=BOTTOM)
        
        self.exit_btn = Button(self.exit_frame, text="Exit", 
        font=self.fonte, width=5)
        self.exit_btn["command"] = quit
        self.exit_btn.pack(side=RIGHT)

    def _start_tun(self):
        print(self.tun_in.get(), self.tun_out.get())

        uav_out_ip = get_ip(self.tun_out.get())
        uav_in_data = config_tunnel(self.tun_in.get(), self.tun_name.get())
        uav_out_data = config_tunnel(self.tun_out.get(), self.tun_name.get())
        print(uav_out_ip, uav_in_data, uav_out_data)
        data = send_command(uav_out_ip, "-U").decode("utf-8")
        if data == "-A":
            print("OK")
            send_command(uav_out_ip, "-S_" + uav_in_data + " " + uav_out_data)



def send_command(ip, command):
    bytesToSend         = str.encode(command)
    serverAddressPort   = (ip, 8000)
    bufferSize          = 1024
    # Create a UDP socket at client side
    UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    #Send to server using created UDP socket
    UDPClientSocket.sendto(bytesToSend, serverAddressPort)
    msgFromServer = UDPClientSocket.recvfrom(bufferSize)
    data = msgFromServer[0]
    print(data)
    return data

def receive_ready_status():
    localIP     = "192.168.56.1"
    localPort   = 8001
    bufferSize  = 1024

    # Create a datagram socket
    UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

    # Bind to address and ip
    UDPServerSocket.bind((localIP, localPort))

    print("Waiting ready status")
    msg = None
    # Listen for incoming datagrams
    while(msg  == None):
        bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)
        msg= bytesAddressPair[0]
        address = bytesAddressPair[1]
        clientIP  = "Client IP Address:{}".format(address)
        print(msg)
        print(clientIP)

    return msg

def config_tunnel(host, tun_name):
    id = re.findall(r'\d+', host)[0]
    last_tun_element = int(re.findall(r'\d+', tun_name)[1])-1
    tun_out_id = int(re.findall(r'\d+', tun_name)[1])
    if host == "Host":
        with open(app_settings_dir + "/base.json") as json_file:
            data = json.load(json_file)
            host_info = data["interfaces"][id-1]
            remote_ip = ipaddress.IPv4Address(data["local_ip"])-1+100+id
            arguments = host_info["name"] + "_" + data["local_ip"] + "_" + str(remote_ip) + "_" + host_info["ip"] + "_" + host_info["network"] + host_info["network_mask"]
    else:
        with open(app_settings_dir + "/"+ host +".json") as json_file:
            id = int(re.findall(r'\d+', host)[0])
            data = json.load(json_file)
            host_info = data["interfaces"][last_tun_element]
            if id > 1:
                remote_ip = ipaddress.IPv4Address(data["local_ip"])-id+1
            else:
                remote_ip = ipaddress.IPv4Address(data["local_ip"])-id+tun_out_id
                
            arguments = host_info["name"] + "_" + data["local_ip"] + "_" + str(remote_ip) + "_" + host_info["ip"] + "_" + host_info["network"] + host_info["network_mask"]
        
    return arguments

def get_ip(host, tun=None):
    with open(app_settings_dir + "/"+ host +".json") as json_file:
        data = json.load(json_file)
        if tun is not None:
            host_info = data["interfaces"][0]
            ip = host_info["ip"]
        else:
            ip = data["local_ip"]
    return ip


root = Tk()
Application(root)
root.geometry("300x350+300+300")
root.mainloop()