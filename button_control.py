
import tkinter as tk
import serial
import time


arduino = serial.Serial('COM6', 115200, timeout=.1)

# def getData():
#  	while True:
#          a = arduino.readline()
#          if data:
#              return(data.decode("utf-8"))
# def function(entry):
#     print(entry)

def send_to_arduino(message):
    if isinstance(message, int):
        arduino.write(str(message).encode())
        print("Sent Message: " + str(message))
    else:
        arduino.write(message.encode())
        print("Sent Message: " + message)
    # print(getData())
    
def read_slider(event):
    val = speed_slider.get()
    send_to_arduino(val)
    
    


window = tk.Tk()

# slider_label = tk.Label(window, text = "Set the Center Speed")
# slider_label.pack()
# speed_slider = tk.Scale(window, from_= 0, to = 100, orient='horizontal', length = 300, command = read_slider)
# speed_slider.pack()
# speed_slider.set(50)
stop_button = tk.Button(window, text="Stop MO!", command = lambda: send_to_arduino("stop"))
stop_button.pack()
go_button = tk.Button(window, text="Go MO Go!", command = lambda: send_to_arduino("go"))
go_button.pack()

snail_mode = tk.Button(window, text="Snail Mode", command = lambda: send_to_arduino("snail"))
snail_mode.pack()

normal_mode = tk.Button(window, text="Normal Mode", command = lambda: send_to_arduino("normal"))
normal_mode.pack()

XTreme_mode = tk.Button(window, text="XTREME MODE !!1!!!", command = lambda: send_to_arduino("extreme"))
XTreme_mode.pack()





# right_forward = tk.Button(window, text="right_forward", command= lambda: send_to_arduino("rightF"))
# right_forward.pack()
# right_backward = tk.Button(window, text="right_backward", command= lambda: send_to_arduino("rightB"))
# right_backward.pack()
# right_stop = tk.Button(window, text="right_stop", command= lambda: send_to_arduino("rightS"))
# right_stop.pack()
# left_forward = tk.Button(window, text="left_forward", command= lambda: send_to_arduino("leftF"))
# left_forward.pack()
# left_backward = tk.Button(window, text="left_backward", command= lambda: send_to_arduino("leftB"))
# left_backward.pack()
# left_stop = tk.Button(window, text="left_stop", command= lambda: send_to_arduino("leftS"))
# left_stop.pack()

# speed = tk.

window.mainloop()
