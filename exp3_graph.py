import matplotlib.pyplot as plt


threads = [1, 2, 4, 8]
time = [0.883470, 0.462842, 0.558043, 0.584899]

plt.plot(threads, time, marker='o')
plt.xlabel("Number of Threads")
plt.ylabel("Execution Time (seconds)")
plt.title("Exp-3: Heat Diffusion – Execution Time vs Threads")
plt.grid(True)

plt.savefig("exp3_heat_execution_time.png", bbox_inches='tight')

plt.show()
