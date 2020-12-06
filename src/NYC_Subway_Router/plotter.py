import os
import pandas as pd
import plotly.express as px
import plotly.graph_objects as go

stops = pd.read_csv("/Users/annahampton/Documents/COP3530/City_Folk/src/NYC_Subway_Router/route.csv")
os.remove("/Users/annahampton/Documents/COP3530/City_Folk/src/NYC_Subway_Router/route.csv")
fig_title = f"Route from {stops['Stop Name'][0]} to {list(stops['Stop Name'])[-1]}"

fig = go.Figure(go.Scattermapbox(
    mode = "markers+lines",
    lat = stops["Latitude"],
    lon = stops["Longitude"],
    hovertext = stops["Stop Name"],
    marker = {'size': 8},
    )
)

fig.update_layout(
    mapbox = {
        'style': "carto-positron",
        'center': {'lon':stops["Longitude"].mean(), 'lat':stops["Latitude"].mean()},
        'zoom' : 10
    },
    title=fig_title
    
)
fig.write_html("route.html")
os.system("open ./route.html")


