'''
    Imports
'''

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

'''
    Global Variables
'''

id = 0
config_drone_buttons = list()
add_drone_buttons = list()
add_tunnel_buttons = list()
tun_name_entries = list()
tun_in_entries = list()
tun_out_entries = list()

log_file = os.path.abspath(os.path.join(__file__, "..", "logs","log.log"))
app_scripts_dir = os.path.abspath(os.path.join(__file__,"..","scripts"))
app_settings_dir = os.path.abspath(os.path.join(__file__,"..","settings"))
socket_dir = os.path.abspath(os.path.join(__file__,"..", "..", "config"))



'''
    Class definitions
'''
# 
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

        self.lblqgc = Label(self.container2, 
        text="qGroundControl:", font=self.fonte, width=15)
        self.lblqgc.pack(side=LEFT)

        self.open_qGC = Button(self.container2, text="Open", 
        font=self.fonte, width=15)
        self.open_qGC["command"] = self._open_qgc
        self.open_qGC.pack(side=RIGHT)

        self.container3 = Frame(master)
        self.container3["padx"] = 20
        self.container3["pady"] = 5
        self.container3.pack()

        self.lblbase = Label(self.container3, 
        text="Base:", font=self.fonte, width=15)
        self.lblbase.pack(side=LEFT)

        self.config_base = Button(self.container3, text="Config", 
        font=self.fonte, width=15)
        self.config_base["command"] = self._config_base
        self.config_base.pack(side=RIGHT)

        self.container4 = Frame(master)
        self.container4["padx"] = 20
        self.container4["pady"] = 5
        self.container4.pack()
        
        self.lbluav = Label(self.container4, 
        text="Add drone:", font=self.fonte, width=15)
        self.lbluav.pack(side=LEFT)

        self.add_drone = Button(self.container4, text="Add", 
        font=self.fonte, width=15)
        self.add_drone["command"] = self._add_drone
        self.add_drone.pack(side=RIGHT)

        self.container6 = Frame(master)
        self.container6["pady"] = 10
        self.container6.pack(side = TOP)

        self.lbluav = Label(self.container6, 
        text="Add Tunnel:", font=self.fonte, width=15)
        self.lbluav.pack(side=LEFT)

        self.add_tunnel = Button(self.container6, text="Add", 
        font=self.fonte, width=15)
        self.add_tunnel["command"] = self._add_tunnel
        self.add_tunnel.pack(side=RIGHT)

        self.exit_frame = Frame(master)
        self.exit_frame["padx"] = 20
        self.exit_frame["pady"] = 5
        self.exit_frame.pack(side=BOTTOM)

        self.exit_btn = Button(self.exit_frame, text="Exit", 
        font=self.fonte, width=5)
        self.exit_btn["command"] = quit
        self.exit_btn.pack(side=RIGHT)

    def _open_qgc(self):
        print(get_time() +" Open QGroundControl SW")
        logger.info("Open QGroundControl SW")
        qgc_path = os.path.abspath(os.path.join(__file__, "..", "..", "..", "..", ".."))
        subprocess.Popen(qgc_path+"/QGroundControl.AppImage", shell=True)

    def _add_drone(self, master=None):
        #Define a UAV ID
        global id
        id = id + 1

        self.container5 = Frame(master)
        self.container5["pady"] = 10
        self.container5.pack(side = TOP)

        self.lbluav = Label(self.container5, 
        text="Drone "+str(id)+":", font=self.fonte, width=10)
        self.lbluav.pack(side=LEFT)
        
        self.config_drone = Button(self.container5, text="Config", 
        font=self.fonte, width=10)
        config_drone_buttons.append(self.config_drone)
        config_index = config_drone_buttons.index(self.config_drone) + 1
        self.config_drone["command"] = lambda i=config_index: self._config_drone(i)
        self.config_drone.pack(side=LEFT)

        self.start_drone = Button(self.container5, text="Start", 
        font=self.fonte, width=10)
        add_drone_buttons.append(self.start_drone)
        add_index = add_drone_buttons.index(self.start_drone) + 1
        self.start_drone["command"] = lambda i=add_index: self._start_drone(i)
        self.start_drone.pack(side=RIGHT)
        
    def _config_base(self):
        print(get_time() +" Configure Base Settings")
        logger.info("Configure Base Settings")

    def _start_drone(self, btn_id):
        # self.start_drone["text"] = "Stop"
        # self.start_drone["command"] = lambda: self._stop_drone(btn_id)
        
        time_str = datetime.now().strftime("[%d/%m/%Y, %H:%M:%S,%f]")
        print(get_time() +" Start UAV #" + str(btn_id))
        logger.info(" Start UAV #" + str(btn_id))
        
        #Start VM related with drone ID
        subprocess.Popen(shlex.split("sh " + app_scripts_dir + "/start_vm TEDI-GUEST" + str(btn_id)))
        sleep(2)
        ready = receive_ready_status().decode("utf-8")
        print("Wait ready status")
        if ready == "-R":
            print(get_time() + " UAV #{} is ready".format(btn_id))
            sleep(2)
            self._start_up_system(btn_id, get_time())
        
    def _start_up_system(self, btn_id, time_str):
        #Send Alive Check
        uav_ip = get_ip("uav"+ str(btn_id))
        logger.info("Send Alive Check Message: UAV #"+ str(btn_id) + ": " + uav_ip)
        print(get_time() +" Send Alive Message: UAV #"+ str(btn_id) + ": " + uav_ip)
        response = send_command(uav_ip, "-A").decode("utf-8")
        print(get_time() +" UAV #" + str(btn_id)+ " status: " + response)
        logger.info("UAV #" + str(btn_id)+ " status: " + response)
        
        #Send config command to base
        cmd_args = config_tunnel("Host", btn_id)
        print_command_args("Base", cmd_args)
        logger.info(log_command_args("Base", cmd_args))
        base_ip = get_ip("base")
        print("Base IP: ", base_ip)
        base_response = send_command(base_ip, "-T_" + cmd_args).decode("utf-8")
        print(get_time() +" Configuration on Base: " + base_response)
        logger.info("Configuration on Base: " + base_response)

        sleep(2)

        #Send config command to drone
        uav_cmd_args = config_tunnel("uav"+str(btn_id), btn_id)
        print_command_args("UAV #"+ str(btn_id) , uav_cmd_args)
        logger.info(log_command_args("UAV #"+ str(btn_id) , uav_cmd_args) )
        print("Drone IP: ", uav_ip)
        uav_response = send_command(uav_ip, "-T_" + uav_cmd_args).decode("utf-8")
        print(get_time() +" Configuration on UAV #"+ str(btn_id) + ": " + uav_response)
        # self.command_message_print(" Tunnel Config on UAV"+ str(btn_id) + ": " + uav_response)
        logger.info(" Configuration on UAV #"+ str(btn_id) + ": " + uav_response)

        #Check Alive drone with tunnel
        uav_ip = get_ip("uav"+ str(btn_id), "tun")
        for i in range(0, 3):   
            response = send_command(uav_ip, "-A").decode("utf-8")
            print(get_time() +" Alive Check UAV #" + str(btn_id)+ ": " + response)
            # self.command_message_print("Tunnel on Drone TEDI-GUEST" + str(btn_id)+ " status: " + response)
            logger.info("Alive Check UAV #" + str(btn_id)+ ": " + response)
            time.sleep(1)
        
        #Send Init Firmware
        # response = send_command(uav_ip, "-I_"+str(btn_id)).decode("utf-8")
        # print(get_time() +" Firmware on Drone TEDI-GUEST" + str(btn_id)+ " status: " + response)
        # # self.command_message_print("Firmware on Drone TEDI-GUEST" + str(btn_id)+ " status: " + response)
        # logger.info("Firmware on Drone TEDI-GUEST" + str(btn_id)+ " status: " + response)
        # time.sleep(1)
            
    def _stop_drone(self, btn_id):
        self.start_drone["text"] = "Start"
        self.start_drone["command"] = lambda: self._start_drone(btn_id)

        #do stuff for shutdown drone

    def _config_drone(self, btn_id, master=None):
        print("config_drone id: " + str(btn_id))
        
        # self.newwin = Toplevel(master)

        # self.newwin.container = Frame(self.newwin)
        # self.newwin.container["pady"] = 10
        # self.newwin.container.pack()

        # self.newwin.title = Label(self.newwin.container, borderwidth=1 , text="Settings - Drone " + str(btn_id))
        # self.newwin.title["font"] = ("Calibri", "9", "bold")
        # self.newwin.title.grid(row=0,column=1)

        # self.lblnetwork = Label(self.newwin.container, 
        # text="network:", font=self.fonte, width=15)
        # self.lblnetwork.grid(row=1,column=0)

        # self.entnetwork = Entry(self.newwin.container, font=self.fonte, width=15)
        # self.entnetwork.grid(row=1,column=1)

        # self.newwin.container1 = Frame(self.newwin)
        # self.newwin.container1["padx"] = 20
        # self.newwin.container1["pady"] = 5
        # self.newwin.container1.pack()

        # self.lblqgc = Label(self.newwin.container1, 
        # text="qGroundControl:", font=self.fonte, width=15)
        # self.lblqgc.pack(side=TOP)

        # self.newwin.exit_btn = Button(self.newwin, text="Exit", 
        # font=self.fonte, width=15)
        # self.newwin.exit_btn["command"] = self.newwin.destroy
        # self.newwin.exit_btn.pack(side=BOTTOM)

    def _add_tunnel(self, master=None):
        self.container5 = Frame(master)
        self.container5["pady"] = 10
        self.container5.pack(side = TOP)
 
        self.lbluav = Label(self.container5, 
        text="Tunnel Name: ", font=self.fonte, width=15)
        self.lbluav.pack(side=LEFT)

        self.tun_name = Entry(self.container5, font=self.fonte, width=10)
        tun_name_entries.append(self.tun_name)
        self.tun_name.pack(side=LEFT)

        self.container6 = Frame(master)
        self.container6["pady"] = 10
        self.container6.pack(side = TOP)

        self.tun_in = Entry(self.container6, font=self.fonte, width=5)
        tun_in_entries.append(self.tun_in)
        self.tun_in.pack(side=LEFT)

        self.lbldir = Label(self.container6, 
        text="=>", font=self.fonte, width=2)
        self.lbldir.pack(side=LEFT)

        self.tun_out = Entry(self.container6, font=self.fonte, width=5)
        tun_out_entries.append(self.tun_out)
        self.tun_out.pack(side=LEFT)

        self.create_tun = Button(self.container6, text="Create", 
        font=self.fonte, width=10)
        add_tunnel_buttons.append(self.create_tun)
        add_index = add_tunnel_buttons.index(self.create_tun) 
        self.create_tun["command"] = lambda i=add_index: self._create_tun(i)
        self.create_tun.pack(side=RIGHT)

        # self.config_drone = Button(self.container5, text="Config", 
        # font=self.fonte, width=10)
        # config_drone_buttons.append(self.config_drone)
        # config_index = config_drone_buttons.index(self.config_drone) + 1
        # self.config_drone["command"] = lambda i=config_index: self._config_drone(i)
        # self.config_drone.pack(side=LEFT)

        # self.start_drone = Button(self.container5, text="Start", 
        # font=self.fonte, width=10)
        # add_drone_buttons.append(self.start_drone)
        # add_index = add_drone_buttons.index(self.start_drone) + 1
        # self.start_drone["command"] = lambda i=add_index: self._start_drone(i)
        # self.start_drone.pack(side=RIGHT)

    def _create_tun(self, id):
        print("Start Tunnel Configuration")
        print("\tTun uav_in: {}\n\tTun uav_out: {}\n\ttun_name: {}".format(
            tun_in_entries[id].get(), tun_out_entries[id].get(), tun_name_entries[id].get()))
        
        uav_out_ip = get_ip(tun_out_entries[id].get())
        uav_in_data = config_uav_tunnel(tun_in_entries[id].get(), tun_name_entries[id].get(), "in")
        uav_out_data = config_uav_tunnel(tun_out_entries[id].get(), tun_name_entries[id].get(), "out")
        print("UAV IP: {}\nUAV IN: {}\nUAV OUT: {}".format(uav_out_ip, uav_in_data, uav_out_data))

        data = send_command(uav_out_ip, "-U").decode("utf-8")
        if data == "-A":
            send_command(uav_out_ip, "-S_" + uav_in_data + " " + uav_out_data)
        
# class DroneButton(Button):
#     drone_id = 0
#     def __init__(self,master=None, width=10, font=("Verdana", "8")):
#         Button.__init__(self, master, text="Start", font=font, width=width)
#         #self.drone_button = Button(master, text="Start", font=font, width=width)
        
                
'''
    Function definitions
'''
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

def config_tunnel(host, id):
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
            host_info = data["interfaces"][0]
            remote_ip = ipaddress.IPv4Address(data["local_ip"])-100-id+1
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

def sleep(time_given):
    for i in range(0, time_given):
        print("Waiting " + str(i) + "s")
        time.sleep(1)
    
def create_timed_rotating_log(path,):
    """"""
    logger = logging.getLogger("UAVApp")
    logger.setLevel(logging.INFO)
#   fh = logging.FileHandler(path)
    
    formatter = logging.Formatter('[%(asctime)s]|%(name)s|%(levelname)s|%(message)s')

    handler = handlers.RotatingFileHandler(path, 
                                    maxBytes=1024000,
                                    backupCount=5)
    handler.setLevel(logging.INFO)
    handler.setFormatter(formatter)                                   
    logger.addHandler(handler)
    
    return logger

def config_uav_tunnel(host, tun_name, dir):
    first_element = int(tun_name[3])
    last_element = int(tun_name[5])
    dif = last_element - first_element
    with open(app_settings_dir + "/"+ host +".json") as json_file:
        data = json.load(json_file)
        if dif > 1:
            if dir == "in":
                remote_ip = ipaddress.IPv4Address(data["local_ip"])+dif
            elif dir == "out":
                remote_ip = ipaddress.IPv4Address(data["local_ip"])-dif
        elif dif == 1: 
            if dir == "in":
                remote_ip = ipaddress.IPv4Address(data["local_ip"])+1
            elif dir == "out":
                remote_ip = ipaddress.IPv4Address(data["local_ip"])-1
        else: 
            remote_ip = "ERROR on get remote_ip"
        network = get_network(data["interfaces"], tun_name)
        ip = get_tun_ip(data["interfaces"], tun_name)
        arguments = tun_name + "_" + data["local_ip"] + "_" + str(remote_ip) + "_" + ip + "_" + network
    return arguments

def get_network(dict_objects, name):
    for dict in dict_objects:
        if dict['name'] == name:
            return dict['network'] + dict['network_mask']

def get_tun_ip(dict_objects, name):
    for dict in dict_objects:
        if dict['name'] == name:
            return dict['ip']

def get_time():
    now=datetime.now()
    date_hour=now.strftime("%d/%m/%Y, %H:%M:%S")
    usecs=int(now.strftime("%f"))
    msecs=int(round(usecs/1000))
    time_str = "[{},{}]".format(date_hour, msecs)
    return time_str

def print_command_args(dst_str ,command_args):
    tun_name, local_ip, remote_ip, tun_ip, tun_network = command_args.split("_")
    print(get_time() + 
        " Configuration Parameters of {}\n\
        Tunnel Name: {}\n\
        Local IP: {}\n\
        Remote IP: {}\n\
        Tunnel IP: {}\n\
        Tunnel Network: {}".format(dst_str,tun_name, local_ip, remote_ip, tun_ip, tun_network)
    )
def log_command_args(dst_str, command_args):
    tun_name, local_ip, remote_ip, tun_ip, tun_network = command_args.split("_")
    log_str = "Configuration Parameters of {}\n\tTunnel Name: {}\n\tLocal IP: {}\n\tRemote IP: {}\n\tTunnel IP: {}\n\tTunnel Network: {}".format(dst_str, tun_name, local_ip, remote_ip, tun_ip, tun_network)
    return log_str
def open_server():
    subprocess.Popen(shlex.split("sh " + socket_dir + "/start_socket_server.sh"))
'''
    Function Calls
'''

root = Tk()
Application(root)
root.geometry("300x650+300+300")
logger = create_timed_rotating_log(log_file)
logger.info("------- UAVApp Start Execution -------")
open_server()
root.mainloop()
