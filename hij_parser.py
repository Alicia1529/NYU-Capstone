import numpy as np
filename = "External_hij/data/test2.txt"
fp = open(filename, "r")
dtype = "complex128"

content = fp.readlines()

pi= 4.0*np.arctan(1.0)
p = 0.05
# (real, imag)
z = 0.05 + 0.j
t = 30.0/180 * pi
p = 130.0/180 * pi
nmax = 14
dimt = 2 * nmax * (nmax + 2)
hij = np.empty((dimt, dimt), dtype=dtype)

idx = 0
for line in content:
    row = idx // dimt
    col = idx % dimt
    # col = idx // dimt
    # row = idx % dimt
    each = eval(line.split(":")[1].strip())
    re = each[0]
    im = each[1]
    hij[row, col] = re + im*1.j
    idx += 1

print(hij)