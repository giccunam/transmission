#!/usr/bin/env python3

import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from time import sleep
#from matplotlib.animation import FuncAnimation
import matplotlib.patches as patches


ccolor=['k','r','g']
# Data for plotting

#t = np.arange(0.0, 2.0, 0.01)
#s = 1 + np.sin(2 * np.pi * t)

with open("view2D.dat") as f:
    data = f.readlines()

iterations, npeople, x_As, x_Bs, y_As, y_Bs,r_circle = data[0].split("\t")
x_A = float(x_As)
x_B = float(x_Bs)
y_A = float(y_As)
y_B = float(y_Bs)
r_circle=float(r_circle)


iterations = iterations[1:]

npeople = int(npeople)
iterations = int(iterations)

X = [[] for x in range(npeople)]
Y = [[] for x in range(npeople)]
C = [[] for x in range(npeople)]

fig, ax = plt.subplots()
iterator = 0

for line in data[1:]:
    if "#" in line[0]:
        iteration, healty,sick,immune,dead = line.split("\t")
        iteration=int(iteration[1:])
        plt.cla()
        ax.set(xlabel='x', ylabel='y',
               title='TICS UNAM Transmission')
        plt.axis([x_A, x_B,  y_A, y_B])        
        ax.grid()
        iterator = 0
    else:
        age, gender, status, time_recovery, position, velocity = line.split("\t")
        position = position[1:-2]
        #print(position)
        x,y = position.split(",")
        x = float(x)
        y=float(y)
        c=int(status)
        circle = plt.Circle((x, y), r_circle, color=ccolor[c])
        ax.add_artist(circle)
        iterator = iterator + 1

    if (iterator == npeople):
        rect = patches.Rectangle((-47,-42),24,24,color='k',alpha=0.2,fill=True)
        ax.add_patch(rect)
        plt.text(-45,-25, "Healty: "+healty , fontsize=12)
        plt.text(-45,-30, "Sick: "+sick, fontsize=12,color='r')
        plt.text(-45,-35, "Immune: "+immune, fontsize=12,color='g')
        plt.text(-45,-45, "Dead: "+dead,color='b', fontsize=12)        
        plt.draw()
        #plt.show()        
        #break
        fig.savefig("animation3/"+("%04d"%iteration)+"-view2D.png")
