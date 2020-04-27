import sys, os
path2add = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__))))

if (not (path2add in sys.path)) :
    sys.path.append(path2add)


import time
import numpy as np
import pickle

import SphericalTMatrix as sm
from parameter_parser import parameter_parser
from RCTMA import rctma

def oaec(lbd, nmat, T, J):
    Cext = 0.0
    nbp = T.shape[0]
    for i in range(nbp):
        for j in range(nbp):
            sub = T[i, j].transpose()
            if (i == j):
                Cext += sub.trace().real
            else:
                dot = sub * J[j, i]
                Cext += dot.trace().real

    k0 = 2.0 * np.pi / lbd
    k0m = k0 * nmat
    Cext =  - Cext * 2.0  * np.pi / k0m /k0m
    return Cext


if __name__ == "__main__":
    import pickle
    
    num = 9
    nmax = 3

    time1 = time.time()
    lbd, n0, particles = parameter_parser()

    T = rctma(num, nmax, lbd, n0, particles)
    J = pickle.load(open("Validation_Data/J.npy", "rb"))

    Cext = oaec(lbd, n0, T, J)
    print("Cext:", Cext)
