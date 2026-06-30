import numpy as np
import matplotlib.pyplot as plt

# Deterministic seed
np.random.seed(42)

x = np.linspace(0, 10, 1000)
y = np.sin(x)

plt.plot(x, y)
plt.title("Sample Reproducible Figure")
plt.savefig("results/figures/sample_figure.pdf")
plt.close()

print("Results generated successfully.")