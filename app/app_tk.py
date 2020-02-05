import os
import subprocess
from tkinter import *

id = 0
class Application:    
    def __init__(self, master=None):
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

        self.exit_btn = Button(master, text="Exit", 
        font=self.fonte, width=5)
        self.exit_btn["command"] = quit
        self.exit_btn.pack(side=BOTTOM)

    def _open_qgc(self):
        print("open_qgc")
        qgc_path = os.path.abspath(os.path.join(__file__, "..", "..", "..", "..", ".."))
        subprocess.Popen(qgc_path+"/QGroundControl.AppImage", shell=True)

        def _add_drone(self, master=None):
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
        self.config_drone["command"] = lambda: self._config_drone(id)
        self.config_drone.pack(side=LEFT)

        self.start_drone = Button(self.container5, text="Start", 
        font=self.fonte, width=10)
        self.start_drone["command"] = lambda: self._start_drone(id)
        self.start_drone.pack(side=RIGHT)
        
        print("add_drone opt")

    def _config_base(self):
        print("config_base")

    def _start_drone(self, btn_id):
        print("start_drone")

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
                
root = Tk()
Application(root)
root.geometry("300x200+300+300")
root.mainloop()