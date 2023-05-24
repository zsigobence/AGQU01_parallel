import matplotlib.pyplot as plt

x = []
y = []

with open("results.txt", "r") as file:
    for line_index, line in enumerate(file):
        data = line.split()
        if line_index == 0:
            parallel_line_y = int(data[0])
        else:
            x.append(int(data[0]))
            y.append(int(data[1]))

plt.plot(x, y)


plt.axhline(y=parallel_line_y, color='r', linestyle='--')

plt.xlabel("Number of threads")
plt.ylabel("Time")
plt.title("Data")

plt.show()
