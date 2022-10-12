import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import plotly.express as px

df = pd.read_csv("data2part_10000.txt", names=["p", "t", "x", "y", "z", "vx", "vy", "vz"], sep=" ")

# ---------- SINGLE PARTICLE : z(t) ----------
fig1 = px.line(df[df.p==1], x='t', y='z', template='simple_white')
fig1.write_image("single_z.pdf")


# ---------- TWO PARTICLES : XY PLANE ----------
fig2 = px.line(df, x='x', y='y', color='p', template='simple_white')

#equivalent to plt.exis('same')
fig2.update_yaxes(
    scaleanchor = "x",
    scaleratio = 1,
  )
fig2.write_image("double_xy.pdf")


# ---------- TWO PARTICLES : PHASE SPACE X ----------
fig3 = px.line(df, x='x', y='vx', color='p', template='simple_white')

#equivalent to plt.exis('same')
fig3.update_yaxes(
    scaleanchor = "x",
    scaleratio = 1,
  )
fig3.write_image("double_xvx.pdf")


# ---------- TWO PARTICLES : PHASE SPACE Z ----------
fig4 = px.line(df, x='z', y='vz', color='p', template='simple_white')

#equivalent to plt.exis('same')
fig4.update_yaxes(
    scaleanchor = "x",
    scaleratio = 1,
  )
fig4.write_image("double_zvz.pdf")

# ---------- TWO PARTICLES : XYZ ----------
fig5 = px.line_3d(df, x="x", y="y", z="z", color='p', template='simple_white')
fig5.write_image("double_xyz.pdf")