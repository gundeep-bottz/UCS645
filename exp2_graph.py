import matplotlib.pyplot as plt


threads = [1, 2, 4, 8]
time = [0.00015, 0.005134, 0.001740, 0.002456]


plt.plot(threads, time, marker='o')
plt.xlabel("Number of Threads")
plt.ylabel("Execution Time (seconds)")
plt.title("Exp-2: Execution Time vs Number of Threads (Smith-Waterman)")
plt.grid(True)

plt.show()
