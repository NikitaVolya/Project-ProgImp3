import matplotlib.pyplot as plt

type_value1 = ""
type_value2 = ""

values1 = []
values2 = []


with open("data_time.txt") as f:
  header = f.readline().split()
  type_value1, type_value2 = header[0], header[1]

  for x in f:
    parts = x.split()
    values1.append(float(parts[0]))
    values2.append(float(parts[1]))

print(values1)
print(values2)


plt.title("evolution du "+type_value1+" par rapport au "+type_value2+".")
plt.xlabel(type_value1)
plt.ylabel(type_value2)
plt.plot(values1, values2)

plt.savefig('graphique.png', dpi=300)