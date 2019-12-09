from tkinter import *
from tkinter.ttk import *

class Application(Frame):

    def __init__(self):
        super().__init__()
        self.initUI()

    def close(self):
        print("Close App!!")
    
    def start_uav_frame(self, master=None):
        self.uav_frame = Frame(master)

        self.uav_frame.pack(side = TOP)
        self.uav_opt(self.uav_frame)

    def initUI(self):

        self.master.title("UAVSys")
        self.style = Style()
        self.style.theme_use("default")
        frame = Frame(self, relief=RAISED, borderwidth=1)
        frame.pack(fill=BOTH, expand=True)
        self.pack(fill=BOTH, expand=True)

        closeButton = Button(self, text="Exit")
        closeButton.command = self.master.quit
        closeButton.pack(side=RIGHT, padx=5, pady=5)
        okButton = Button(self, text="OK")
        okButton.pack(side=RIGHT)

def main():
    root = Tk()
    root.geometry("300x200+300+300")
    app = Application()
    root.mainloop()
    root.destroy()

if __name__ == '__main__':
    main()