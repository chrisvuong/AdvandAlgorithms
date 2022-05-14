# %%
import matplotlib.pyplot as plt

# %%
fig, ax = plt.subplots()
# plot horizontalines
plt.hlines(y=3, xmin=2, xmax=4, linewidth=2, color='black')
plt.hlines(y=6, xmin=6, xmax=12, linewidth=2, color='black')
plt.hlines(y=6, xmin=14, xmax=17, linewidth=2, color='black')
plt.hlines(y=7, xmin=16, xmax=20, linewidth=2, color='black')
plt.hlines(y=9, xmin=3, xmax=10, linewidth=2, color='black')
plt.hlines(y=9, xmin=17, xmax=27, linewidth=2, color='black')
plt.hlines(y=11, xmin=9, xmax=16, linewidth=2, color='black')
plt.hlines(y=13, xmin=6, xmax=10, linewidth=2, color='black')
plt.hlines(y=14, xmin=15, xmax=17, linewidth=2, color='black')
plt.hlines(y=14, xmin=18, xmax=23, linewidth=2, color='black')
plt.hlines(y=16, xmin=6, xmax=13, linewidth=2, color='black')
# plot vertical
plt.vlines(x=    [4, 7, 10,11,13,15,16,18,21,22], 
            ymin=[5, 5, 7 ,12,2 ,5 ,12,6 ,12,6 ],
           ymax= [12,17,12,17,12,12,15,12,18,10], colors='teal', ls='-', lw=2)

# plot intersect
plt.plot(4, 9, marker="o", markersize=5, color="red")
plt.plot(7, 9, marker="o", markersize=5, color="red")
plt.plot(10, 9, marker="o", markersize=5, color="red")
plt.plot(7, 6, marker="o", markersize=5, color="red")
plt.plot(7, 16, marker="o", markersize=5, color="red")
plt.plot(7, 13, marker="o", markersize=5, color="red")
plt.plot(10, 11, marker="o", markersize=5, color="red")
plt.plot(11, 16, marker="o", markersize=5, color="red")
plt.plot(13, 11, marker="o", markersize=5, color="red")
plt.plot(15, 11, marker="o", markersize=5, color="red")
plt.plot(15, 6, marker="o", markersize=5, color="red")
plt.plot(16, 14, marker="o", markersize=5, color="red")
plt.plot(18, 7, marker="o", markersize=5, color="red")
plt.plot(18, 9, marker="o", markersize=5, color="red")
plt.plot(21, 14, marker="o", markersize=5, color="red")
plt.plot(22, 9, marker="o", markersize=5, color="red")
ax.minorticks_on()
plt.grid(which = "major", linestyle='-')
plt.grid(which = "minor", linestyle=':')
plt.xlim([0,28])
plt.ylim([0,20])
plt.xlabel("X")
plt.ylabel("Y")
plt.show()

# %%



