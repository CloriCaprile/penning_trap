import pandas as pd
import matplotlib.pyplot as plt

df_int = pd.read_csv("../build/data2part_int_64000.txt", names=["p", "t", "x", "y", "z", "vx", "vy", "vz"], sep=" ")
df_nonint = pd.read_csv("../build/data2part_nonint_64000.txt", names=["p", "t", "x", "y", "z", "vx", "vy", "vz"], sep=" ")

# Plot style options
w = 10
h = 5
fontsize = 12
save_fig = True


