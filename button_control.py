import tkinter as tk
import serial
import time


arduino = serial.Serial('COM6', 115200, timeout=.1)

def getData():
	while True:
		data = arduino.readline()
		if data:
			return(data.decode("utf-8"))
def function(entry):
    print(entry)

def send_to_arduino(message):
	arduino.write(message.encode())
	print(getData())


window = tk.Tk()
greeting = tk.Label(text="Hello, Tkinter")
greeting.pack()

right_forward = tk.Button(window, text="right_forward", command= lambda: send_to_arduino("rightF"))
right_forward.pack()
right_backward = tk.Button(window, text="right_backward", command= lambda: send_to_arduino("rightB"))
right_backward.pack()
right_stop = tk.Button(window, text="right_stop", command= lambda: send_to_arduino("rightS"))
right_stop.pack()
left_forward = tk.Button(window, text="left_forward", command= lambda: send_to_arduino("leftF"))
left_forward.pack()
left_backward = tk.Button(window, text="left_backward", command= lambda: send_to_arduino("leftB"))
left_backward.pack()
left_stop = tk.Button(window, text="left_stop", command= lambda: send_to_arduino("leftS"))
left_stop.pack()

window.mainloop()