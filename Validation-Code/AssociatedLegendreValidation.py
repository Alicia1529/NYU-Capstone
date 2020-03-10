import numpy as np
import scipy.special as sp

print("""
Associated Legendre Function
----------------------------
nmax          : 14
Theta (deg)   : 1.850000000e+01
cTheta        : 9.483236552e-01
----------------------------""")
print("    n                Pnm               Pinm              Taunm")

nmax = 14
degree = 18.5
theta = np.radians([degree])[0]
ctheta = np.cos(theta)
# print(theta)
# print(ctheta)

pmn_pos, dpmn_pos = sp.lpmn(nmax, nmax, ctheta)
dpmn_pos = np.multiply(dpmn_pos, -np.sin(theta))
pmn_neg, dpmn_neg = sp.lpmn(-nmax, nmax, ctheta)
dpmn_neg = np.multiply(dpmn_neg, -np.sin(theta))
if theta % np.pi != 0:
    for n in range(nmax+1):
        for m in range(n, -n-1, -1):
            if m >= 0:
                pmn = pmn_pos[m][n]
                taumn = dpmn_pos[m][n]
            else:
                pmn = pmn_neg[-m][n]
                taumn = dpmn_neg[-m][n]
            pimn = m*pmn/np.sin(theta)
            print("{:>5}{:>5}{:>19.9e}{:>19.9e}{:>19.9e}"
                .format(n, m, pmn, pimn, taumn)
                )
else:
    for n in range(nmax+1):
        for m in range(n, -n-1, -1):
            if m >= 0:
                pmn = pmn_pos[m][n]
            else:
                pmn = pmn_neg[-m][n]
            if m != 1 and m != -1:
                pimn = 0
                taumn = 0
            elif m == 1:
                pimn = 1/2*n*(n+1)*np.power(-1,m)
                taumn = 1/2*n*(n+1)*np.power(-1,n+m)
            elif m == -1:
                if n == 0:
                    pimn = -1/2*np.power(-1,m)
                else:
                    pimn = 1/2*np.power(-1,n+m)
                taumn = 1/2*np.power(-1,n+m+1)
            print("{:>5}{:>5}{:>19.9e}{:>19.9e}{:>19.9e}"
                .format(n, m, pmn, pimn, taumn)
                )