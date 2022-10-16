import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.legend_handler import HandlerTuple

df_int = pd.read_csv("../build/data2part_int_64000.txt", names=["p", "t", "x", "y", "z", "vx", "vy", "vz"], sep=" ")
df_nonint = pd.read_csv("../build/data2part_nonint_64000.txt", names=["p", "t", "x", "y", "z", "vx", "vy", "vz"], sep=" ")
mask_p1 = (df_nonint.p == 1)
mask_p2 = (df_nonint.p == 2)

# Plot style options
w = 10
h = 5
fontsize = 12
cmap = plt.get_cmap('tab20')
save_fig = True

# ----------------------- time evolution -----------------------

## NON INTERACTING

# x(t) and y(t)
fig, ax1 = plt.subplots(figsize=(w,h))
 
p1, = ax1.plot(df_nonint.t[mask_p1], df_nonint.x[mask_p1], color=cmap(0))
p2, = ax1.plot(df_nonint.t[mask_p2], df_nonint.x[mask_p2], color=cmap(1))
ax1.set_xlabel("$t$ ($\mu$s)")
ax1.set_ylabel("$x$ ($\mu$m)")
ax1.tick_params(axis="y", labelcolor=cmap(0))
ax2 = ax1.twinx()
p3, = ax2.plot(df_nonint.t[mask_p1], df_nonint.y[mask_p1], color=cmap(2))
p4, = ax2.plot(df_nonint.t[mask_p2], df_nonint.y[mask_p2], color=cmap(3))
ax2.set_ylabel("$y$ ($\mu$m)")
ax2.tick_params(axis="y", labelcolor=cmap(2))
plt.legend([(p1, p3), (p2, p4)], ['p1', 'p2'], handler_map={tuple: HandlerTuple(ndivide=None)}, loc='best')
plt.savefig("non_int_xt_yt.pdf") if save_fig else plt.show()
plt.cla()

# z(t)
plt.figure(figsize=(w,h))

plt.plot(df_nonint.t[mask_p1], df_nonint.z[mask_p1], color=cmap(4), label='$z_1(t)$')
plt.plot(df_nonint.t[mask_p2], df_nonint.z[mask_p2], color=cmap(5), label='$z_2(t)$')
plt.xlabel("$t$ ($\mu$s)")
plt.ylabel("$z$ ($\mu$m)")
plt.legend(loc='best')
plt.savefig("non_int_zt.pdf") if save_fig else plt.show()
plt.cla()

## INTERACTING

# x(t) and y(t)
fig, ax1 = plt.subplots(figsize=(w,h))
 
p1, = ax1.plot(df_int.t[mask_p1], df_int.x[mask_p1], color=cmap(0))
p2, = ax1.plot(df_int.t[mask_p2], df_int.x[mask_p2], color=cmap(1))
ax1.set_xlabel("$t$ ($\mu$s)")
ax1.set_ylabel("$x$ ($\mu$m)")
ax1.tick_params(axis="y", labelcolor=cmap(0))
ax2 = ax1.twinx()
p3, = ax2.plot(df_int.t[mask_p1], df_int.y[mask_p1], color=cmap(2))
p4, = ax2.plot(df_int.t[mask_p2], df_int.y[mask_p2], color=cmap(3))
ax2.set_ylabel("$y$ ($\mu$m)")
ax2.tick_params(axis="y", labelcolor=cmap(2))
plt.legend([(p1, p3), (p2, p4)], ['p1', 'p2'], handler_map={tuple: HandlerTuple(ndivide=None)}, loc='best')
plt.savefig("int_xt_yt.pdf") if save_fig else plt.show()
plt.cla()

# z(t)
plt.figure(figsize=(w,h))

plt.plot(df_int.t[mask_p1], df_int.z[mask_p1], color=cmap(4), label='$z_1(t)$')
plt.plot(df_int.t[mask_p2], df_int.z[mask_p2], color=cmap(5), label='$z_2(t)$')
plt.xlabel("$t$ ($\mu$s)")
plt.ylabel("$z$ ($\mu$m)")
plt.legend(loc='best')
plt.savefig("int_zt.pdf") if save_fig else plt.show()
plt.cla()

# ----------------------- XY PLANE -----------------------

## NON INTERACTING

plt.figure(figsize=(w,h))
plt.axis('equal')

p1, = plt.plot(df_nonint.x[mask_p1], df_nonint.y[mask_p1], color=cmap(0))
p2, = plt.plot(df_nonint.x[np.argmax(mask_p1)], df_nonint.y[np.argmax(mask_p1)], 'o', color=cmap(1))
p3, = plt.plot(df_nonint.x[mask_p2], df_nonint.y[mask_p2], color=cmap(2))
p4, = plt.plot(df_nonint.x[np.argmax(mask_p2)], df_nonint.y[np.argmax(mask_p2)], 'o', color=cmap(3))
plt.legend([p1, p3, (p2, p4)], ['p1', 'p2', 'initial state'], handler_map={tuple: HandlerTuple(ndivide=None)}, loc='best')
plt.xlabel("$x$ ($\mu$m)")
plt.ylabel("$y$ ($\mu$m)")
plt.savefig("non_int_xy.pdf") if save_fig else plt.show()
plt.cla()

## INTERACTING

plt.figure(figsize=(w,h))
plt.axis('equal')

p1, = plt.plot(df_int.x[mask_p1], df_int.y[mask_p1], color=cmap(0))
p2, = plt.plot(df_int.x[np.argmax(mask_p1)], df_int.y[np.argmax(mask_p1)], 'o', color=cmap(1))
p3, = plt.plot(df_int.x[mask_p2], df_int.y[mask_p2], color=cmap(2))
p4, = plt.plot(df_int.x[np.argmax(mask_p2)], df_int.y[np.argmax(mask_p2)], 'o', color=cmap(3))
plt.legend([p1, p3, (p2, p4)], ['p1', 'p2', 'initial state'], handler_map={tuple: HandlerTuple(ndivide=None)}, loc='best')
plt.xlabel("$x$ ($\mu$m)")
plt.ylabel("$y$ ($\mu$m)")
plt.savefig("int_xy.pdf") if save_fig else plt.show()
plt.cla()

# ----------------------- X PHASE SPACE -----------------------

## NON INTERACTING

plt.figure(figsize=(w,h))
plt.axis('equal')

p1, = plt.plot(df_nonint.x[mask_p1], df_nonint.vx[mask_p1], color=cmap(0))
p2, = plt.plot(df_nonint.x[np.argmax(mask_p1)], df_nonint.vx[np.argmax(mask_p1)], 'o', color=cmap(1))
p3, = plt.plot(df_nonint.x[mask_p2], df_nonint.vx[mask_p2], color=cmap(2))
p4, = plt.plot(df_nonint.x[np.argmax(mask_p2)], df_nonint.vx[np.argmax(mask_p2)], 'o', color=cmap(3))
plt.legend([p1, p3, (p2, p4)], ['p1', 'p2', 'initial state'], handler_map={tuple: HandlerTuple(ndivide=None)}, loc='best')
plt.xlabel("$x$ ($\mu$m)")
plt.ylabel("$v_x$ (m/s)")
plt.savefig("non_int_xvx.pdf") if save_fig else plt.show()
plt.cla()

## INTERACTING

plt.figure(figsize=(w,h))
plt.axis('equal')

p1, = plt.plot(df_int.x[mask_p1], df_int.vx[mask_p1], color=cmap(0))
p2, = plt.plot(df_int.x[np.argmax(mask_p1)], df_int.vx[np.argmax(mask_p1)], 'o', color=cmap(1))
p3, = plt.plot(df_int.x[mask_p2], df_int.vx[mask_p2], color=cmap(2))
p4, = plt.plot(df_int.x[np.argmax(mask_p2)], df_int.vx[np.argmax(mask_p2)], 'o', color=cmap(3))
plt.legend([p1, p3, (p2, p4)], ['p1', 'p2', 'initial state'], handler_map={tuple: HandlerTuple(ndivide=None)}, loc='best')
plt.xlabel("$x$ ($\mu$m)")
plt.ylabel("$v_x$ (m/s)")
plt.savefig("int_xvx.pdf") if save_fig else plt.show()
plt.cla()

# ----------------------- Z PHASE SPACE -----------------------

## NON INTERACTING

plt.figure(figsize=(w,h))
plt.axis('equal')

p1, = plt.plot(df_nonint.z[mask_p1], df_nonint.vz[mask_p1], color=cmap(0))
p2, = plt.plot(df_nonint.z[np.argmax(mask_p1)], df_nonint.vz[np.argmax(mask_p1)], 'o', color=cmap(1))
p3, = plt.plot(df_nonint.z[mask_p2], df_nonint.vz[mask_p2], color=cmap(2))
p4, = plt.plot(df_nonint.z[np.argmax(mask_p2)], df_nonint.vz[np.argmax(mask_p2)], 'o', color=cmap(3))
plt.legend([p1, p3, (p2, p4)], ['p1', 'p2', 'initial state'], handler_map={tuple: HandlerTuple(ndivide=None)}, loc='best')
plt.xlabel("$z$ ($\mu$m)")
plt.ylabel("$v_z$ (m/s)")
plt.savefig("non_int_zvz.pdf") if save_fig else plt.show()
plt.cla()

## INTERACTING

plt.figure(figsize=(w,h))
plt.axis('equal')

p1, = plt.plot(df_int.z[mask_p1], df_int.vz[mask_p1], color=cmap(0))
p2, = plt.plot(df_int.z[np.argmax(mask_p1)], df_int.vz[np.argmax(mask_p1)], 'o', color=cmap(1))
p3, = plt.plot(df_int.z[mask_p2], df_int.vz[mask_p2], color=cmap(2))
p4, = plt.plot(df_int.z[np.argmax(mask_p2)], df_int.vz[np.argmax(mask_p2)], 'o', color=cmap(3))
plt.legend([p1, p3, (p2, p4)], ['p1', 'p2', 'initial state'], handler_map={tuple: HandlerTuple(ndivide=None)}, loc='best')
plt.xlabel("$z$ ($\mu$m)")
plt.ylabel("$v_z$ (m/s)")
plt.savefig("int_zvz.pdf") if save_fig else plt.show()
plt.cla()