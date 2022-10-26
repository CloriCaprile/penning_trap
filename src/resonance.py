import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.legend_handler import HandlerTuple

# number of particles 
N = 100

df1 = pd.read_csv("../build/tresonance_nonint_0.100000_0.005000.txt", names=["omega", "n"], sep=" ")
df2 = pd.read_csv("../build/tresonance_nonint_0.400000_0.005000.txt", names=["omega", "n"], sep=" ")
df3 = pd.read_csv("../build/tresonance_nonint_0.700000_0.005000.txt", names=["omega", "n"], sep=" ")

df4 = pd.read_csv("../build/42resonance_int_0.100000_0.005000.txt", names=["omega", "n"], sep=" ")
df5 = pd.read_csv("../build/42resonance_int_0.400000_0.005000.txt", names=["omega", "n"], sep=" ")
df6 = pd.read_csv("../build/42resonance_int_0.700000_0.005000.txt", names=["omega", "n"], sep=" ")


# Plot style options
w = 7
h = 5
fontsize = 12
cmap = plt.get_cmap('tab20')
save_fig = True
 
plt.figure(figsize=(w,h))



plt.plot(df1.omega, df1.n/N, color=cmap(0),linestyle='dotted')
plt.plot(df2.omega, df2.n/N, color=cmap(2),linestyle='dotted')
plt.plot(df3.omega, df3.n/N, color=cmap(4),linestyle='dotted')
plt.plot(df4.omega, df4.n/N, color=cmap(0))
plt.plot(df5.omega, df5.n/N, color=cmap(2))
plt.plot(df6.omega, df6.n/N, color=cmap(4))
plt.xlabel("$\omega$ (MHz)")
plt.ylabel("$N/N_0$")
plt.legend(["f=0.1 non-int" , "f=0.4 non-int", "f=0.7 non-int", "f=0.1 int","f=0.4 int","f=0.7 int"], loc ="lower left", prop={'size': 8})
plt.savefig("sresonance_nonint.pdf") if save_fig else plt.show()
plt.cla()