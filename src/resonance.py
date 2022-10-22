import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.legend_handler import HandlerTuple

df1 = pd.read_csv("../build/resonance_int_0.100000.txt", names=["omega", "n"], sep=" ")
df2 = pd.read_csv("../build/resonance_int_0.400000.txt", names=["omega", "n"], sep=" ")
df3 = pd.read_csv("../build/resonance_int_0.700000.txt", names=["omega", "n"], sep=" ")

# Plot style options
w = 5
h = 5
fontsize = 12
cmap = plt.get_cmap('tab20')
save_fig = True
 
plt.figure(figsize=(w,h))

plt.plot(df1.omega, df1.n, color=cmap(0))
plt.plot(df2.omega, df2.n, color=cmap(2))
plt.plot(df3.omega, df3.n, color=cmap(4))
plt.xlabel("$\omega$ (Hz)")
plt.ylabel("$n$")
plt.legend(loc='best')
plt.savefig("resonance.pdf") if save_fig else plt.show()
plt.cla()