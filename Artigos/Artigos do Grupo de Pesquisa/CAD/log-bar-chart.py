import matplotlib.pyplot as plt
import numpy as np

data = ((57.62, 1.29, 0.25), (84.71, 2.00, 0.41), (71.03, 1.86, 0.56), (482.99, 8.42, 1.17))

dim = len(data[0])
w = 0.75
dimw = w / dim

fig, ax = plt.subplots()
x = np.arange(len(data))
for i in range(len(data[0])):
    y = [d[i] for d in data]
    b = ax.bar(x + i * dimw, y, dimw, bottom=0.001)

ax.set_xticks(range(4))
ax.set_yscale('log')

ax.set_xlabel('datasets', fontsize=16)
ax.set_ylabel('time (s)', fontsize=16)

ax.tick_params(axis='both', which='major', labelsize=13)

plt.ylim((0.1, 1000))

plt.legend(['CPU', 'GPUDouble', 'GPUFloat'], fontsize=13, loc='upper left')
plt.show()
