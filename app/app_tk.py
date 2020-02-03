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

        self.lblbase = Label(self.container2, 
        text="Base:", font=self.fonte, width=15)
        self.lblbase.pack(side=LEFT)

        self.config_base = Button(self.container2, text="Config", 
        font=self.fonte, width=15)
        self.config_base["command"] = self._config_base
        self.config_base.pack(side=RIGHT)

        self.container3 = Frame(master)
        self.container3["padx"] = 20
        self.container3["pady"] = 5
        self.container3.pack()

        self.lblqgc = Label(self.container3, 
        text="qGroundControl:", font=self.fonte, width=15)
        self.lblqgc.pack(side=LEFT)

        self.open_qGC = Button(self.container3, text="Open", 
        font=self.fonte, width=15)
        self.open_qGC["command"] = self._open_qgc
        self.open_qGC.pack(side=RIGHT)

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
        self.container6["padx"] = 20
        self.container6["pady"] = 5
        self.container6.pack()

        self.exit_btn = Button(self.container6, text="Exit", 
        font=self.fonte, width=15)
        self.exit_btn["command"] = quit
        self.exit_btn.pack(side=RIGHT)

    
    def command(self):
        print("button clicked")

    
    def _open_qgc(self):
        print("open_qgc")

    def _config_base(self):
        print("config_base")
    
    def _start_drone(self, btn_id):
        print("start_drone")

    def _config_drone(self, btn_id, master=None):
        newwin = Toplevel(master)
        newwin.container6 = Frame(master)
        newwin.container6["padx"] = 20
        newwin.container6["pady"] = 5
        newwin.container6.pack()

        newwin.exit_btn = Button(newwin.container6, text="Exit", 
        font=self.fonte, width=15)
        newwin.exit_btn["command"] = quit
        newwin.exit_btn.pack(side=RIGHT)

        display = Label(newwin, text="Humm, see a new window !")

        display.pack() 

        print("config_drone id: " + str(btn_id))
    
    def _add_drone(self, master=None):
        global id
        id = id + 1
        self.container5 = Frame(master)
        self.container5["pady"] = 10
        self.container5.pack()

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


        
root = Tk()
Application(root)
root.mainloop()