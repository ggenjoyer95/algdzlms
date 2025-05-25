import matplotlib.pyplot as plt
import numpy as np

prefixes = ["cm", "cq", "a1m", "a1q", "mr", "mrq"]
labels = [
    "Merge классический",
    "Quick классический",
    "String Merge",
    "String Quick",
    "MSD Radix",
    "MSD+Quick"
]
colors = ["tab:blue", "tab:orange", "tab:green", "tab:red", "tab:purple", "tab:brown"]
styles = ['-', '--', '-.', ':', '-.', ':']

data_cmp = {}
data_time = {}

for p in prefixes:
    fn_cmp = f"{p}c.txt"
    with open(fn_cmp, "r") as f:
        data_cmp[p] = sorted([float(line) for line in f if line.strip()])
    fn_time = f"{p}t.txt"
    with open(fn_time, "r") as f:
        data_time[p] = sorted([float(line) for line in f if line.strip()])

n = len(data_cmp[prefixes[0]])
x = np.arange(n)
plt.figure(figsize=(10, 6))
for i, p in enumerate(prefixes):
    plt.plot(x, data_cmp[p], label=labels[i], color=colors[i], linestyle=styles[i])
plt.title("Посимвольные сравнения (логарифмическая шкала)")
plt.yscale("log")
plt.grid(True, which="both", ls="--", lw=0.5)
plt.legend()
plt.tight_layout()
plt.savefig("comp.png")

plt.figure(figsize=(10, 6))
for i, p in enumerate(prefixes):
    plt.plot(x, data_time[p], label=labels[i], color=colors[i], linestyle=styles[i])
plt.title("Время работы (логарифмическая шкала)")
plt.yscale("log")
plt.grid(True, which="both", ls="--", lw=0.5)
plt.legend()
plt.tight_layout()
plt.savefig("time.png")
