import matplotlib.pyplot as plt
import sys

def read_data(path):
    values_x = []
    values_y = []
    with open(path) as f:
        header = f.readline().split()
        label_y, label_x = header[0], header[1]
        for line in f:
            parts = line.split()
            values_y.append(float(parts[0]))
            values_x.append(float(parts[1]))
    return label_x, label_y, values_x, values_y

label_x, label_y, x1, y1 = read_data(sys.argv[1])
_,       _,       x2, y2 = read_data(sys.argv[2])

plt.title("Evolution du " + label_y + " par rapport au " + label_x + ".")
plt.xlabel(label_x)
plt.ylabel(label_y)
plt.plot(x1, y1, label="liste")
plt.plot(x2, y2, label="arbre")
plt.legend()

plt.savefig(sys.argv[3], dpi=300)
plt.savefig(sys.argv[3].replace('.svg', '.png'), dpi=300)
