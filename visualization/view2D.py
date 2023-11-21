#!/usr/bin/env python3

import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from time import sleep
from matplotlib.animation import FuncAnimation


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
    else:
        age, gender, status, time_recovery, position, velocity = line.split("\t")
        position = position[1:-2]
        #print(position)
        x,y = position.split(",")
        x = float(x)
        y=float(y)
        c=int(status)
        #print(iterator)
        #print(c)
        X[iterator].append(x)
        Y[iterator].append(y)
        C[iterator].append(c)
        
        if iterator == npeople-1:
            iterator = 0
        else:
            iterator = iterator+1

#print(X)
#print(Y)
#print(C)
            
ax.set(xlabel='x', ylabel='y',
       title='view2D')
plt.axis([x_A, x_B,  y_A, y_B])
#legend((line1, line2, line3), ('label1', 'label2', 'label3'))


ax.grid()

#n = 0
####for b in range(len(X[0])):
for b in range(1):
    plt.cla()
    ax.set(xlabel='x', ylabel='y',
           title='TICS UNAM Transmission')
    plt.axis([x_A, x_B,  y_A, y_B])        
    #plt.text(-40,-10, "Healty: "+, fontsize=12)
    #plt.text(-40,-20, "Sick: ", fontsize=12)
    #plt.text(-40,-30, "Immune: ", fontsize=12)
    #plt.text(-40,-40, "Dead: ", fontsize=12)
    ax.grid()

    for u,v,c in zip(X,Y,C):
        #if n>1:
        #    ax.plot(u[:b-1], v[:b-1],'ro')
        #n=n+1
        thecolor=c[b]
        #thecolor=u[b-1:b]
        #print(thecolor)
        circle = plt.Circle((u[b], v[b]), r_circle, color=ccolor[thecolor])
        ax.add_artist(circle)
        #ax.plot(u[b:b+1], v[b:b+1],'o',color=ccolor[thecolor])
    plt.draw()

#plt.show()

    #######fig.savefig("animation/"+("%04d"%b)+"-view2D.png")




    #plt.pause(0.0001) 



####def update(i):
####    for u,v,c in zip(X,Y,C):
####        #if n>1:
####        #    ax.plot(u[:b-1], v[:b-1],'ro')
####        #n=n+1
####        thecolor=c[i]
####        #thecolor=u[b-1:b]
####        #print(thecolor)
####        circle = plt.Circle((u[i], v[i]), r_circle, color=ccolor[thecolor])
####        ax.add_artist(circle)
####        #ax.plot(u[b:b+1], v[b:b+1],'o',color=ccolor[thecolor])
####
####    #x = np.linspace(0, 4, 1000)
####    #y = np.sin(2 * np.pi * (x - 0.01 * i))
####    #line.set_data(x, y)
####    #return ax,    
####
####    
####animation = FuncAnimation(fig, update, interval=10)
####plt.show()
####    
####    
#fig.savefig("view2D.png")
#plt.show()


