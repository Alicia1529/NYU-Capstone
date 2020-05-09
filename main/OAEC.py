import sys, os
path2add = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__))))

if (not (path2add in sys.path)) :
    sys.path.append(path2add)


import time
import numpy as np
import pickle

import SphericalTMatrix as sm
from parameter_parser import parameter_parser
from data_parser import data_parser
# from RCTMA import rctma

def oaec(lbd, nmat, T, J):
    Cext = 0.0
    nbp = T.shape[0]
    for i in range(nbp):
        for j in range(nbp):
            if (i == j):
                Cext += T[i, j].trace().real
            else:
                dot = T[i, j] @ J[j, i]
                Cext += dot.trace().real

    k0 = 2.0 * np.pi / lbd
    k0m = k0 * nmat
    Cext =  - Cext * 2.0  * np.pi / k0m /k0m
    return Cext


if __name__ == "__main__":
    import pickle
    import os
    test_num = 1
    parallelize  = True
    config_num = {1: 9, 2: 14, 3:10, 4: 9, 5: 13, 6:3}
    num = config_num[test_num]
    nmax = 3

    if parallelize:
        import ray
        print("#"*50)
        print(sys.argv)
        # redis_password = sys.argv[1]
        # num_workers = int(sys.argv[2])
        # os.environ["ip_head"] = "10.214.97.24:6379"
        ray.init(address="auto")

        print("Nodes in the Ray cluster:")
        print(ray.nodes())

        from RCTMA_parallel import rctma
    else:
        from RCTMA_sequential import rctma

    IN_FILE = "InputDataC{}.txt".format(str(test_num))

    time1 = time.time()
    lbd, n0, particles = parameter_parser(nmax, IN_FILE)
    os.system("module load cmake")
    os.system("cmake external/CMakeLists.txt")
    os.system("(cd external && make)") 
    os.system("./external/external_hij")  
    data_parser(num, nmax)

    time2 = time.time()
    print("Time for preparing Hij is:", time2 - time1)

    T = rctma(num, nmax, lbd, n0, particles)
    time3 = time.time()
    print("Time for computing vscatter and rcmta matrices is:", time3 - time2)
 
    J = pickle.load(open("external/data/J.npy", "rb"))
    Cext = oaec(lbd, n0, T, J)
    time4 = time.time()
    print("Cext:", Cext)
    print("Time for reading Jij and computing OAEC is :", time4 - time3)
