import matplotlib.pyplot as plt

data = {
    500: {1: 317, 2: 185, 5: 117, 10: 57, 25: 57, 50: 48, 100: 47},
    1000: {1: 2790, 2: 1512, 5: 765, 10: 471, 25: 438, 50: 393, 100: 413},
    1500: {1: 12113, 2: 6548, 5: 2758, 10: 1884, 25: 1696, 50: 1653, 100: 1558},
    2000: {1: 30694, 2: 16454, 5: 7400, 10: 5504, 25: 5346, 50: 4786, 100: 4714},
    2500: {1: 58764, 2: 31302, 5: 15302, 10: 10947, 25: 10922, 50: 10522, 100: 10410},
}

colors = {
    1: 'blue', 2: 'red', 5: 'orange', 10: 'green',
    25: 'purple', 50: 'brown', 100: 'pink'
}

for thread_count in data[500].keys():
    x = sorted(data.keys())
    y = [data[n][thread_count] for n in x]
    plt.plot(x, y, label=f"{thread_count} поток(ов)", color=colors.get(thread_count, None))

plt.title("Зависимость времени перемножения матриц от N и числа потоков")
plt.xlabel("Размер матрицы N")
plt.ylabel("Время (мс)")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
