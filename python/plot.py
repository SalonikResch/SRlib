import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np

x = range(10)
y = np.random.random((2,10))

names = ['Name1', 'Name2']
colors =  ['Red', 'Blue']
patches = [mpatches.Patch(color=color,label=name) for (color,name) in zip(colors,names)]

for i, result in enumerate(names):
    plt.scatter(x,y[i,:],color=colors[i])

plt.legend('top left',handles=patches)
plt.ylabel('Y label')
plt.xlabel('X label')
plt.savefig('figure.png')