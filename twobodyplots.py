import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots

df_int = pd.read_csv("data2part_int_10000.txt", names=["p", "t", "x", "y", "z", "vx", "vy", "vz"], sep=" ")
df_nonint = pd.read_csv("data2part_nonint_10000.txt", names=["p", "t", "x", "y", "z", "vx", "vy", "vz"], sep=" ")

savefigs = True

fig = make_subplots(
    rows=2, cols=2, 
    specs=[[{'type': 'scatter'}, {'type': 'scatter'}],
           [{'type': 'scatter'}, {'type': 'scatter'}]],
    subplot_titles=("$z_1(t)$", "xy plane", "Phase space of x", "Phase space of z"))

# ---------- SINGLE PARTICLE : z(t) ----------
fig.add_trace(
    go.Scatter(x=df_int.t[df_int.p==1], y=df_int.z[df_int.p==1],
        mode='lines',
        #marker_symbol="diamond", 
        marker_color="deepskyblue", 
        marker_size=1,
        showlegend=False),
    row=1,col=1
)
fig.update_xaxes(title_text="t", row=1, col=1)
fig.update_yaxes(title_text="z", row=1, col=1)

# ---------- TWO PARTICLES : XY PLANE ----------
fig.add_trace(
    go.Scatter(x=df_int.x[df_int.p==1], y=df_int.y[df_int.p==1],
        mode='lines', 
        marker_color="deepskyblue", 
        marker_size=1,
        showlegend=False),
    row=1,col=2
)
fig.add_trace(
    go.Scatter(x=df_int.x[df_int.p==2], y=df_int.y[df_int.p==2], 
        mode='lines', 
        marker_color="orangered",
        marker_size=1,
        showlegend=False),
    row=1,col=2
)

fig.add_trace(
    go.Scatter(x=[df_int.x[0]], y=[df_int.y[0]], 
        mode='markers',
        marker_symbol="square", 
        marker_color="blue",
        marker_size=10,
        showlegend=False),
    row=1,col=2
)

fig.add_trace(
    go.Scatter(x=[df_int.x[10001]], y=[df_int.y[10001]], 
        mode='markers',
        marker_symbol="diamond", 
        marker_color="red",
        marker_size=10,
        showlegend=False),
    row=1,col=2
)

fig.update_xaxes(title_text="x", row=1, col=2)
fig.update_yaxes(title_text="y",
                scaleratio = 1,
                row=1, col=2)


# ---------- TWO PARTICLES : PHASE SPACE X ----------
fig.add_trace(
    go.Scatter(x=df_int.x[df_int.p==1], y=df_int.vx[df_int.p==1],
        mode='lines', 
        marker_color="deepskyblue", 
        marker_size=1,
        showlegend=False),
    row=2,col=1
)
fig.add_trace(
    go.Scatter(x=df_int.x[df_int.p==2], y=df_int.vx[df_int.p==2], 
        mode='lines', 
        marker_color="orangered",
        marker_size=1,
        showlegend=False),
    row=2,col=1
)

fig.add_trace(
    go.Scatter(x=[df_int.x[0]], y=[df_int.vx[0]], 
        mode='markers',
        marker_symbol="square", 
        marker_color="blue",
        marker_size=10,
        showlegend=False),
    row=2,col=1
)

fig.add_trace(
    go.Scatter(x=[df_int.x[10001]], y=[df_int.vx[10001]], 
        mode='markers',
        marker_symbol="diamond", 
        marker_color="red",
        marker_size=10,
        showlegend=False),
    row=2,col=1
)

fig.update_xaxes(title_text="x",
                row=2, col=1)
fig.update_yaxes(title_text="vx",
                row=2, col=1)


# ---------- TWO PARTICLES : PHASE SPACE Z ----------
fig.add_trace(
    go.Scatter(x=df_int.z[df_int.p==1], y=df_int.vz[df_int.p==1],
        mode='lines', 
        marker_color="deepskyblue", 
        marker_size=1,
        showlegend=False),
    row=2,col=2
)
fig.add_trace(
    go.Scatter(x=df_int.z[df_int.p==2], y=df_int.vz[df_int.p==2], 
        mode='lines', 
        marker_color="orangered",
        marker_size=1,
        showlegend=False),
    row=2,col=2
)

fig.add_trace(
    go.Scatter(x=[df_int.z[0]], y=[df_int.vz[0]], 
        mode='markers',
        marker_symbol="square", 
        marker_color="blue",
        marker_size=10,
        showlegend=False),
    row=2,col=2
)

fig.add_trace(
    go.Scatter(x=[df_int.z[10001]], y=[df_int.vz[10001]], 
        mode='markers',
        marker_symbol="diamond", 
        marker_color="red",
        marker_size=10,
        showlegend=False),
    row=2,col=2
)

fig.update_xaxes(title_text="z", 
                scaleanchor = "y",
                scaleratio = 1,
                row=2, col=2)
fig.update_yaxes(title_text="vz", 
                row=2, col=2)

fig.update_layout(template='simple_white', height=1000, width=1000)
if savefigs:
    fig.write_image("problem8_int.pdf")
else:
    fig.show()
    
    
# ----------------------------------- NON INTERACTING ----------------------------------- 

fig = make_subplots(
    rows=2, cols=2, 
    specs=[[{'type': 'scatter'}, {'type': 'scatter'}],
           [{'type': 'scatter'}, {'type': 'scatter'}]],
    subplot_titles=("$z_1(t)$", "xy plane", "Phase space of x", "Phase space of z"))

# ---------- SINGLE PARTICLE : z(t) ----------
fig.add_trace(
    go.Scatter(x=df_nonint.t[df_nonint.p==1], y=df_nonint.z[df_nonint.p==1],
        mode='lines',
        #marker_symbol="diamond", 
        marker_color="deepskyblue", 
        marker_size=1,
        showlegend=False),
    row=1,col=1
)
fig.update_xaxes(title_text="t", row=1, col=1)
fig.update_yaxes(title_text="z", row=1, col=1)

# ---------- TWO PARTICLES : XY PLANE ----------
fig.add_trace(
    go.Scatter(x=df_nonint.x[df_nonint.p==1], y=df_nonint.y[df_nonint.p==1],
        mode='lines', 
        marker_color="deepskyblue", 
        marker_size=1,
        showlegend=False),
    row=1,col=2
)
fig.add_trace(
    go.Scatter(x=df_nonint.x[df_nonint.p==2], y=df_nonint.y[df_nonint.p==2], 
        mode='lines', 
        marker_color="orangered",
        marker_size=1,
        showlegend=False),
    row=1,col=2
)

fig.add_trace(
    go.Scatter(x=[df_nonint.x[0]], y=[df_nonint.y[0]], 
        mode='markers',
        marker_symbol="square", 
        marker_color="blue",
        marker_size=10,
        showlegend=False),
    row=1,col=2
)

fig.add_trace(
    go.Scatter(x=[df_nonint.x[10001]], y=[df_nonint.y[10001]], 
        mode='markers',
        marker_symbol="diamond", 
        marker_color="red",
        marker_size=10,
        showlegend=False),
    row=1,col=2
)

fig.update_xaxes(title_text="x", row=1, col=2)
fig.update_yaxes(title_text="y",
                scaleratio = 1,
                row=1, col=2)


# ---------- TWO PARTICLES : PHASE SPACE X ----------
fig.add_trace(
    go.Scatter(x=df_nonint.x[df_nonint.p==1], y=df_nonint.vx[df_nonint.p==1],
        mode='lines', 
        marker_color="deepskyblue", 
        marker_size=1,
        showlegend=False),
    row=2,col=1
)
fig.add_trace(
    go.Scatter(x=df_nonint.x[df_nonint.p==2], y=df_nonint.vx[df_nonint.p==2], 
        mode='lines', 
        marker_color="orangered",
        marker_size=1,
        showlegend=False),
    row=2,col=1
)

fig.add_trace(
    go.Scatter(x=[df_nonint.x[0]], y=[df_nonint.vx[0]], 
        mode='markers',
        marker_symbol="square", 
        marker_color="blue",
        marker_size=10,
        showlegend=False),
    row=2,col=1
)

fig.add_trace(
    go.Scatter(x=[df_nonint.x[10001]], y=[df_nonint.vx[10001]], 
        mode='markers',
        marker_symbol="diamond", 
        marker_color="red",
        marker_size=10,
        showlegend=False),
    row=2,col=1
)

fig.update_xaxes(title_text="x",
                row=2, col=1)
fig.update_yaxes(title_text="vx",
                row=2, col=1)


# ---------- TWO PARTICLES : PHASE SPACE Z ----------
fig.add_trace(
    go.Scatter(x=df_nonint.z[df_nonint.p==1], y=df_nonint.vz[df_nonint.p==1],
        mode='lines', 
        marker_color="deepskyblue", 
        marker_size=1,
        showlegend=False),
    row=2,col=2
)
fig.add_trace(
    go.Scatter(x=df_nonint.z[df_nonint.p==2], y=df_nonint.vz[df_nonint.p==2], 
        mode='lines', 
        marker_color="orangered",
        marker_size=1,
        showlegend=False),
    row=2,col=2
)

fig.add_trace(
    go.Scatter(x=[df_nonint.z[0]], y=[df_nonint.vz[0]], 
        mode='markers',
        marker_symbol="square", 
        marker_color="blue",
        marker_size=10,
        showlegend=False),
    row=2,col=2
)

fig.add_trace(
    go.Scatter(x=[df_nonint.z[10001]], y=[df_nonint.vz[10001]], 
        mode='markers',
        marker_symbol="diamond", 
        marker_color="red",
        marker_size=10,
        showlegend=False),
    row=2,col=2
)

fig.update_xaxes(title_text="z", 
                scaleanchor = "y",
                scaleratio = 1,
                row=2, col=2)
fig.update_yaxes(title_text="vz", 
                row=2, col=2)

fig.update_layout(template='simple_white', height=1000, width=1000)
if savefigs:
    fig.write_image("problem8_nonint.pdf")
else:
    fig.show()


# ---------- TWO PARTICLES : XYZ SPACE ----------
fig3d = make_subplots(
    rows=1, cols=2, 
    specs=[[{'type': 'surface'}, {'type': 'surface'}]])

fig3d.update_yaxes(
    scaleanchor = "x",
    scaleratio = 1,
)

#int
fig3d.add_trace(
    go.Scatter3d(x=df_int.x[df_int.p==1], y=df_int.y[df_int.p==1], z=df_int.z[df_int.p==1],
        mode='lines', 
        marker_color="deepskyblue", 
        marker_size=1,
        showlegend=True),
    row=1,col=1
)
fig3d.add_trace(
    go.Scatter3d(x=df_int.x[df_int.p==2], y=df_int.y[df_int.p==2], z=df_int.z[df_int.p==2],
        mode='lines', 
        marker_color="orangered",
        marker_size=1,
        showlegend=True),
    row=1,col=1
)

fig3d.add_trace(
    go.Scatter3d(x=[df_int.x[0]], y=[df_int.y[0]], z=[df_int.z[0]],
        mode='markers',
        marker_symbol="square", 
        marker_color="blue",
        marker_size=5,
        showlegend=False),
    row=1,col=1
)

fig3d.add_trace(
    go.Scatter3d(x=[df_int.x[10001]], y=[df_int.y[10001]], z=[df_int.z[10001]],
        mode='markers',
        marker_symbol="diamond", 
        marker_color="red",
        marker_size=5,
        showlegend=False),
    row=1,col=1
)

# nonint
fig3d.add_trace(
    go.Scatter3d(x=df_nonint.x[df_nonint.p==1], y=df_nonint.y[df_nonint.p==1], z=df_nonint.z[df_nonint.p==1],
        mode='lines', 
        marker_color="deepskyblue", 
        marker_size=1,
        showlegend=True),
    row=1,col=2
)
fig3d.add_trace(
    go.Scatter3d(x=df_nonint.x[df_nonint.p==2], y=df_nonint.y[df_nonint.p==2], z=df_nonint.z[df_nonint.p==2],
        mode='lines', 
        marker_color="orangered",
        marker_size=1,
        showlegend=True),
    row=1,col=2
)

fig3d.add_trace(
    go.Scatter3d(x=[df_nonint.x[0]], y=[df_nonint.y[0]], z=[df_nonint.z[0]],
        mode='markers',
        marker_symbol="square", 
        marker_color="blue",
        marker_size=5,
        showlegend=False),
    row=1,col=2
)

fig3d.add_trace(
    go.Scatter3d(x=[df_nonint.x[10001]], y=[df_nonint.y[10001]], z=[df_nonint.z[10001]],
        mode='markers',
        marker_symbol="diamond", 
        marker_color="red",
        marker_size=5,
        showlegend=False),
    row=1,col=2
)

fig3d.update_layout(template='simple_white')
if savefigs:
    fig3d.write_image("problem8_3d.pdf")
else:
    fig3d.show()