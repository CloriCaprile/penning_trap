import pandas as pd
import matplotlib.pyplot as plt

err_0004 = pd.read_csv("../build/err_4000.txt",   names=["t", "e_rk", "e_fe"], sep=" ")
err_0008 = pd.read_csv("../build/err_8000.txt",   names=["t", "e_rk", "e_fe"], sep=" ")
err_0016 = pd.read_csv("../build/err_16000.txt",  names=["t", "e_rk", "e_fe"], sep=" ")
err_0032 = pd.read_csv("../build/err_32000.txt",  names=["t", "e_rk", "e_fe"], sep=" ")
err_0064 = pd.read_csv("../build/err_64000.txt",  names=["t", "e_rk", "e_fe"], sep=" ")
err_0128 = pd.read_csv("../build/err_128000.txt", names=["t", "e_rk", "e_fe"], sep=" ")
err_0256 = pd.read_csv("../build/err_256000.txt", names=["t", "e_rk", "e_fe"], sep=" ")
err_1024 = pd.read_csv("../build/err_1024000.txt", names=["t", "e_rk", "e_fe"], sep=" ")

# Plot style options
w = 10
h = 5
fontsize = 12
save_fig = True

# ----------------------- RK.4 -----------------------
plt.figure(figsize=(w,h))

plt.plot(err_0004.t, err_0004.e_rk, label='4k')
plt.plot(err_0008.t, err_0008.e_rk, label='8k')
plt.plot(err_0016.t, err_0016.e_rk, label='16k')
plt.plot(err_0032.t, err_0032.e_rk, label='32k')
plt.legend(loc='best')
plt.savefig("err_rk4.pdf") if save_fig else plt.show()

plt.cla()
plt.figure(figsize=(w,h))

plt.plot(err_0004.t, err_0004.e_rk, label='4k')
plt.plot(err_0008.t, err_0008.e_rk, label='8k')
plt.plot(err_0016.t, err_0016.e_rk, label='16k')
plt.plot(err_0032.t, err_0032.e_rk, label='32k')
plt.plot(err_0064.t, err_0064.e_rk, label='64k')
plt.plot(err_0128.t, err_0128.e_rk, label='128k')
plt.plot(err_0256.t, err_0256.e_rk, label='256k')
plt.plot(err_1024.t, err_1024.e_rk, label='1024k')
plt.legend(loc='best')
plt.savefig("err_rk4_more.pdf") if save_fig else plt.show()

# ------------------------ FE ------------------------
plt.figure(figsize=(w,h))

plt.plot(err_0004.t, err_0004.e_fe, label='4k')
plt.plot(err_0008.t, err_0008.e_fe, label='8k')
plt.plot(err_0016.t, err_0016.e_fe, label='16k')
plt.plot(err_0032.t, err_0032.e_fe, label='32k')
plt.legend(loc='best')
plt.savefig("err_fe.pdf") if save_fig else plt.show()

plt.cla()
plt.figure(figsize=(w,h))

plt.plot(err_0004.t, err_0004.e_fe, label='4k')
plt.plot(err_0008.t, err_0008.e_fe, label='8k')
plt.plot(err_0016.t, err_0016.e_fe, label='16k')
plt.plot(err_0032.t, err_0032.e_fe, label='32k')
plt.plot(err_0064.t, err_0064.e_fe, label='64k')
plt.plot(err_0128.t, err_0128.e_fe, label='128k')
plt.plot(err_0256.t, err_0256.e_fe, label='256k')
plt.plot(err_1024.t, err_1024.e_fe, label='1024k')
plt.legend(loc='best')
plt.savefig("err_fe_more.pdf") if save_fig else plt.show()

# -------------------- Comparison --------------------
plt.figure(figsize=(10,5))
cmap = plt.get_cmap('tab20')

plt.plot(err_0016.t, err_0016.e_rk, color=cmap(0), label='RK4 - 16k')
plt.plot(err_0032.t, err_0032.e_rk, color=cmap(2), label='RK4 - 32k')
plt.plot(err_0064.t, err_0064.e_rk, color=cmap(4), label='RK4 - 64k')

plt.plot(err_0016.t, err_0016.e_fe, color=cmap(1), label='FE - 16k')
plt.plot(err_0032.t, err_0032.e_fe, color=cmap(3), label='FE - 32k')
plt.plot(err_0064.t, err_0064.e_fe, color=cmap(5), label='FE - 64k')

plt.legend(loc='best')
plt.savefig("err_rk4_fe.pdf") if save_fig else plt.show()

