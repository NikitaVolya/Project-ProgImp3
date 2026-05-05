import matplotlib.pyplot as plt
import sys

type_value1 = ""
type_value2 = ""

values1 = []
values2 = []


with open(sys.argv[1]) as f:
  header = f.readline().split()
  type_value1, type_value2 = header[0], header[1]

  for x in f:
    parts = x.split()
    values1.append(float(parts[0]))
    values2.append(float(parts[1]))


plt.title("evolution du "+type_value1+" par rapport au "+type_value2+".")
plt.xlabel(type_value2)
plt.ylabel(type_value1)
plt.plot(values2, values1)

plt.savefig(sys.argv[2], dpi=300)
plt.savefig(sys.argv[2].replace('.svg', '.png'), dpi=300)