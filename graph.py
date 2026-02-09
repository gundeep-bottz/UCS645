import matplotlib.pyplot as plt


threads = [1, 2, 4, 8]
time = [0.009701, 0.017413, 0.008921, 0.007086]

plt.plot(threads, time, marker='o')
plt.xlabel("Number of Threads")
plt.ylabel("Execution Time (seconds)")
plt.title("Execution Time vs Number of Threads")
plt.grid(True)

plt.show()
