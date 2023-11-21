#!/usr/bin/env python3

# Libraries
import plotly.graph_objects as go

# Data path
data_path = '../data/'

# Lists of particles
healthy_particles  = []
diseased_particles = []
immune_particles   = []

# List of names files
files = ['open_border.dat', 'closed_border.dat']

# Open file
with open(data_path + files[1], 'r') as f:
    lines = f.readlines()

# Get number of iterations and particles
num_iterations = int(lines[0].split()[1])
num_particles  = int(lines[0].split()[2])

# Read data and append to lists,
# the particles
for line in lines[1:]:
    if '#' in line:
        _, _, healthy, diseased, immune, *_ = line.split()

        healthy_particles.append(int(healthy))
        diseased_particles.append(int(diseased))
        immune_particles.append(int(immune))

# Create figure
fig = go.Figure()

# Add traces for particles
fig.add_trace(go.Scatter(x = list(range(num_iterations + 1)), y = healthy_particles,  mode = 'lines', name = 'Sanos'))
fig.add_trace(go.Scatter(x = list(range(num_iterations + 1)), y = diseased_particles, mode = 'lines', name = 'Enfermos'))
fig.add_trace(go.Scatter(x = list(range(num_iterations + 1)), y = immune_particles,   mode = 'lines', name = 'Inmunes'))

# Update layout
fig.update_layout(
    xaxis = dict(
        title    = 'Iteración',
        tickmode = 'linear',
        tick0    = 0,
        dtick    = 100,
        showgrid = True,
        gridcolor = 'LightGray'
    ),

    yaxis = dict(
        title    = 'Número de partículas',
        tickmode = 'linear',
        tick0    = 0,
        dtick    = 10,
        showgrid = True,
        gridcolor = 'LightGray'
    ),

    title      = 'Información transmitida con fronteras cerradas en 2,000 iteraciones',
    title_font = dict(size = 24),
    title_x    = 0.5,

    legend = dict(
        x  = 0.01,
        y  = 0.94,
        traceorder = 'normal',
        font       = dict(size = 12),
        bgcolor    = 'rgba(0, 0, 0, 0)'
    ),

    plot_bgcolor  = 'white',
    paper_bgcolor = 'white',
    font = dict(
        family = 'Arial',
        size   = 12,
        color  = 'black'
    ),

    margin = dict(
        l = 50,
        r = 50,
        t = 50,
        b = 50
    ),

    template = None
)

# Show the plot
fig.show()