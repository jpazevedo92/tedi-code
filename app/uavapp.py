'''
    Imports
'''

import os
import subprocess
import shlex
import json
import ipaddress
import socket
from tkinter import *

'''
    Global Variables
'''

id = 0
config_drone_buttons = list()
add_drone_buttons = list()
app_scripts_dir = os.path.abspath(os.path.join(__file__,"..","scripts"))
app_settings_dir = os.path.abspath(os.path.join(__file__,"..","settings"))
socket_dir = os.path.abspath(os.path.join(__file__,"..", "..", "config", "socket"))

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

        self.exit_frame = Frame(master)
        self.exit_frame["padx"] = 20
        self.exit_frame["pady"] = 5
        self.exit_frame.pack(side=BOTTOM)

        self.exit_btn = Button(self.exit_frame, text="Exit", 
        font=self.fonte, width=5)
        self.exit_btn["command"] = quit
        self.exit_btn.pack(side=RIGHT)

        self.command_frame = Frame(master)
        self.command_frame["padx"] = 20
        self.command_frame["pady"] = 5
        self.command_frame.pack(side=BOTTOM)

        self.lblcomand = Label(self.command_frame, 
        text="Command print:", font=self.fonte, width=15)
        self.lblcomand.pack(side=LEFT)

        self.command_entry = Entry(self.command_frame, 
        font=self.fonte, width=25, state=DISABLED, textvariable=self.command_msg, fg='black')
        self.command_entry.config( background="white",disabledbackground="white")
        #self.config_base["command"] = self._config_base
        self.command_entry.pack(side=RIGHT)

    def command_message_print(self, msg):
        self.command_msg.set(msg)

    def _open_qgc(self):
        print("open_qgc")
        qgc_path = os.path.abspath(os.path.join(__file__, "..", "..", "..", "..", ".."))
        subprocess.Popen(qgc_path+"/QGroundControl.AppImage", shell=True)

    def _add_drone(self, master=None):
        global id
        id = id + 1
        print("add_drone opt")
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
        #self.start_drone.drone_id = id
        #self.start_drone = Button(self.container5, text="TEDI-GUEST"+str(id), font=self.fonte, width=10)
        self.start_drone["command"] = lambda i=add_index: self._start_drone(i)
        self.start_drone.pack(side=RIGHT)
        
    def _config_base(self):
        print("config_base")

    def _start_drone(self, btn_id):
        self.command_message_print("Start drone TEDI-GUEST" + str(btn_id))
        print("Start drone TEDI-GUEST" + str(btn_id))
        #Start VM related with drone ID
        #subprocess.Popen(shlex.split("sh " + app_scripts_dir + "/start_vm TEDI-GUEST" + str(btn_id)))
        #Send Alive Check
        response = send_command("192.168.56.1", "-A").decode("utf-8")
        #subprocess.Popen([socket_dir + "/socket", "-C", "vboxnet0", "192.168.56.1", "-A"])
        #subprocess.call("."+ socket_dir + "/socket -C vboxnet0 192.168.56.1 -A")
        self.command_message_print("Drone TEDI-GUEST" + str(btn_id)+ " status: " + response)

        

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
        

    


class DroneButton(Button):
    drone_id = 0
    def __init__(self,master=None, width=10, font=("Verdana", "8")):
        Button.__init__(self, master, text="Start", font=font, width=width)
        #self.drone_button = Button(master, text="Start", font=font, width=width)
        
                
'''
    Function definitions
'''
def send_command(ip, command):
    port = 8080
    buffer_size = 1024
    message = command
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((ip, port))
    s.send(message.encode())
    data = s.recv(buffer_size)
    s.close()
    return data

'''
    Function Calls
'''
root = Tk()
Application(root)
root.geometry("300x350+300+300")
root.mainloop()
