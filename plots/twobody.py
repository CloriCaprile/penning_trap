import pandas as pd
import matplotlib.pyplot as plt

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
plt.figure(figsize=(w,h))

plt.plot(df_nonint.t[mask_p1], df_nonint.x[mask_p1], color=cmap(0), label='p1 - x')
plt.plot(df_nonint.t[mask_p2], df_nonint.x[mask_p2], color=cmap(1), label='p2 - x')
plt.plot(df_nonint.t[mask_p1], df_nonint.y[mask_p1], color=cmap(2), label='p1 - y')
plt.plot(df_nonint.t[mask_p2], df_nonint.y[mask_p2], color=cmap(3), label='p2 - y')
plt.legend(loc='best')
plt.savefig("non_int_xt_yt.pdf") if save_fig else plt.show()

# z(t)
plt.figure(figsize=(w,h))

plt.plot(df_nonint.t[mask_p1], df_nonint.z[mask_p1], color=cmap(4), label='p1 - z')
plt.plot(df_nonint.t[mask_p2], df_nonint.z[mask_p2], color=cmap(5), label='p2 - z')
plt.legend(loc='best')
plt.savefig("non_int_zt.pdf") if save_fig else plt.show()

## INTERACTING

# x(t) and y(t)
plt.figure(figsize=(w,h))

plt.plot(df_int.t[mask_p1], df_int.x[mask_p1], color=cmap(0), label='p1 - x')
plt.plot(df_int.t[mask_p2], df_int.x[mask_p2], color=cmap(1), label='p2 - x')
plt.plot(df_int.t[mask_p1], df_int.y[mask_p1], color=cmap(2), label='p1 - y')
plt.plot(df_int.t[mask_p2], df_int.y[mask_p2], color=cmap(3), label='p2 - y')
plt.legend(loc='best')
plt.savefig("int_xt_yt.pdf") if save_fig else plt.show()

# z(t)
plt.figure(figsize=(w,h))

plt.plot(df_int.t[mask_p1], df_int.z[mask_p1], color=cmap(4), label='p1 - z')
plt.plot(df_int.t[mask_p2], df_int.z[mask_p2], color=cmap(5), label='p2 - z')
plt.legend(loc='best')
plt.savefig("int_zt.pdf") if save_fig else plt.show()

# ----------------------- XY PLANE -----------------------

## NON INTERACTING

plt.figure(figsize=(w,h))

plt.plot(df_nonint.x[mask_p1], df_nonint.y[mask_p1], color=cmap(0), label='p1')
plt.plot(df_nonint.x[mask_p2], df_nonint.y[mask_p2], color=cmap(2), label='p2')
plt.legend(loc='best')
plt.savefig("non_int_xy.pdf") if save_fig else plt.show()

## INTERACTING

plt.figure(figsize=(w,h))

plt.plot(df_int.x[mask_p1], df_int.y[mask_p1], color=cmap(0), label='p1')
plt.plot(df_int.x[mask_p2], df_int.y[mask_p2], color=cmap(2), label='p2')
plt.legend(loc='best')
plt.savefig("int_xy.pdf") if save_fig else plt.show()

# ----------------------- X PHASE SPACE -----------------------

## NON INTERACTING

plt.figure(figsize=(w,h))

plt.plot(df_nonint.x[mask_p1], df_nonint.vx[mask_p1], color=cmap(0), label='p1')
plt.plot(df_nonint.x[mask_p2], df_nonint.vx[mask_p2], color=cmap(2), label='p2')
plt.legend(loc='best')
plt.savefig("non_int_xvx.pdf") if save_fig else plt.show()

## INTERACTING

plt.figure(figsize=(w,h))

plt.plot(df_int.x[mask_p1], df_int.vx[mask_p1], color=cmap(0), label='p1')
plt.plot(df_int.x[mask_p2], df_int.vx[mask_p2], color=cmap(2), label='p2')
plt.legend(loc='best')
plt.savefig("int_xvx.pdf") if save_fig else plt.show()

# ----------------------- Z PHASE SPACE -----------------------

## NON INTERACTING

plt.figure(figsize=(w,h))

plt.plot(df_nonint.z[mask_p1], df_nonint.vz[mask_p1], color=cmap(0), label='p1')
plt.plot(df_nonint.z[mask_p2], df_nonint.vz[mask_p2], color=cmap(2), label='p2')
plt.legend(loc='best')
plt.savefig("non_int_zvz.pdf") if save_fig else plt.show()

## INTERACTING

plt.figure(figsize=(w,h))

plt.plot(df_int.z[mask_p1], df_int.vz[mask_p1], color=cmap(0), label='p1')
plt.plot(df_int.z[mask_p2], df_int.vz[mask_p2], color=cmap(2), label='p2')
plt.legend(loc='best')
plt.savefig("int_zvz.pdf") if save_fig else plt.show()