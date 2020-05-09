import numpy as np
import scipy.special as sp

print("""
Legendre Polynomial
--------------------------
nmax          : 14
Theta         : 3.228859116e-01
Theta (deg)   : 1.850000000e+01
ctheta        : 9.483236552e-01
--------------------------""")
print("    n                 Pn                P'n               P''n")

nmax = 15
Theta = 3.228859116e-01 # however, loss of precision
degtheta = 18.5
ctheta = np.cos(np.deg2rad(degtheta))
# nmax = 15
# Theta = np.pi
# degtheta = np.degrees([Theta])[0]
# ctheta = np.cos(Theta)
# print(degtheta)
# print(ctheta)

pn, dpn = sp.lpn(nmax, ctheta)
# print(pn)
# print(dpn)

ddpn = [0.0, 0.0, 3.0]
for n in range(nmax):
    if n <= 2:
        ddpn_n = ddpn[n]
    else:
        ddpn_n = (2*n - 1) / (n - 2) * ctheta * ddpn[n - 1] - (n + 1)/(n - 2) * ddpn[n - 2]
        ddpn.append(ddpn_n)
    print("{:>5}{:>19.9e}{:>19.9e}{:>19.9e}"
          .format(n, pn[n], dpn[n], ddpn_n)
         )