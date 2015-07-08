from __future__ import division
import pink_noise
import numpy as np

#data = pink_noise.pink_noise(1280000, delta_t=(1/191), fknee=0.5, alpha=2, show_plot=False)
alldata = np.load("2012-12-31--13-17-57_board77_wire1_ch01.npz")
data = alldata["raw"]
intdata = data*(2**23)/max(data)
# Converts the floats to 24 bit integer-spread. We will truncate the decimals later.
myfile = open("data_from_bolo", "w")
for datum in intdata:
    myfile.write(str(int(datum))+ " ")
