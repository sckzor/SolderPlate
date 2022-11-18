import random
import tkinter as Tk
from itertools import count

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

plt.style.use('fivethirtyeight')
# values for first graph
x_vals = []
y_vals = []

index = count()

def animate(i):
    x_vals.append(next(index))
    y_vals.append(random.randint(0, 5))
    
    ax1 = plt.gcf().get_axes()[0]

    ax1.cla()

    ax1.plot(x_vals, y_vals)

root = Tk.Tk()
label = Tk.Label(root, text="Temperature").grid(column=0, row=0)

canvas = FigureCanvasTkAgg(plt.gcf(), master=root)
canvas.get_tk_widget().grid(column=0, row=1)

plt.gcf().subplots(1, 1)
ani = FuncAnimation(plt.gcf(), animate, interval=1000, blit=False)

Tk.mainloop()
