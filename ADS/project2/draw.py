import matplotlib.pyplot as plt

# Input data
vertexes = [23947347, 14081816, 6262104, 3598623, 1890815, 1524453, 1207945, 1070376, 435666]
edges = [58333344, 34292496, 15248146, 8778114, 4657742, 3897636, 2840208, 2712798, 1057066]
simple_times = [27.7025, 10.6847, 4.08197, 2.23336, 1.07784, 0.831884, 0.576363, 0.500018, 0.210458]
binomial_times = [20.5514, 11.7585, 3.94248, 2.3526, 1.03999, 0.687178, 0.457889, 0.392179, 0.163085]
fibonacci_times = [31.2611, 13.9878, 4.16146, 2.51876, 1.30722, 0.891773, 0.667529, 0.597327, 0.23352]

# Plotting
plt.figure(figsize=(12, 6))
plt.plot(vertexes, simple_times, marker='o', label='Simple')
plt.plot(vertexes, binomial_times, marker='s', label='Binomial')
plt.plot(vertexes, fibonacci_times, marker='^', label='Fibonacci')
plt.xlabel('Vertexes')
plt.ylabel('Run Time (s)')
plt.title('Run Times vs. Input Sizes')
plt.legend()
plt.grid(True)
plt.show()