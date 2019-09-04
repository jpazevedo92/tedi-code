#!/usr/bin/python
import Tkinter as tk

baudrates_list = [
	4800,
	7200,
	9600,
	14400,
	19200,
	38400,
	56000,
	57600,
	115200,
	128000
]

root = tk.Tk()
root.title("SERIAL APP GUI")
root.geometry("800x600")

#Title Frame
title_frame = tk.Frame(root, height=50, width=800)
title_frame.pack()
title = tk.Label(title_frame,text="SERIAL APP GUI", font=("Arial Bold", 25))
title.grid(column=0, row=0)

#Options General Frame
options_frame = tk.Frame(root, height=550, width=800)
options_frame.pack(side = tk.BOTTOM)

#Serial Options Subframe
serial_options_frame = tk.Frame(options_frame, height=550, width=400)
serial_options_frame.pack(side = tk.LEFT)

baudrate_frame = tk.Frame(serial_options_frame, height=166, width=400)
baudrate_frame.pack()

baudrate_title = tk.Label(baudrate_frame,text="Baudrate", font=("Arial Bold", 10), width=15)
baudrate_title.pack(side=tk.LEFT)
scrollbar = tk.Scrollbar(baudrate_frame, orient="vertical")
scrollbar.pack( side = tk.RIGHT, fill = tk.Y )
baudrates_listbox = tk.Listbox(baudrate_frame,  bd=1, selectmode=tk.SINGLE, height=1, width=25, yscrollcommand = scrollbar.set)


baudrates_listbox.insert(tk.END, "Selecione uma das opcoes")
for item in baudrates_list:
	baudrates_listbox.insert(tk.END, item)

baudrates_listbox.select_set(0)
baudrates_listbox.pack(side=tk.LEFT, fill=tk.BOTH)
scrollbar.config( command = baudrates_listbox.yview )

#Serial Options Subframe
uav_options_frame = tk.Frame(options_frame, height=550, width=400)
uav_options_frame.pack(side = tk.RIGHT)



# serial_options = tk.Label(options_frame, text="serial_options", font=("Arial Bold", 25))
# serial_options.pack(side=tk.LEFT)
# uav_options = tk.Label(options_frame, text="uav_options", font=("Arial Bold", 25))
# uav_options.pack(side=tk.RIGHT)
# Code to add widgets will go here...
root.mainloop()

