import sys, os
path2add = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__))))

if (not (path2add in sys.path)) :
    sys.path.append(path2add)


import time
import numpy as np
import pickle

import SphericalTMatrix as sm
from parameter_parser import parameter_parser

dtype = 'complex128'

import ray


# print("#"*50)
# print(sys.argv)
# redis_password = sys.argv[1]
# num_workers = int(sys.argv[2])
# os.environ["ip_head"] = "10.214.97.24:6379"
# ray.init(address="auto", redis_password=redis_password)

# print("Nodes in the Ray cluster:")
# print(ray.nodes())


# ray.init(num_cpus=num_workers, ignore_reinit_error=True)


@ray.remote
def step1_parallel(hij, tMatij_n, f, f_start, f_end, dimt, dtype):
    Trans1 = np.zeros((dimt, dimt), dtype=dtype)
    for i in range(f_start, f_end):
        Trans2 = np.zeros((dimt, dimt), dtype=dtype)
        for j in range(1, f):
            Trans2 += tMatij_n[(i)-1, (j)-1] @ hij[(j)-1, (f)-1]
        Trans1 += hij[(f)-1, (i)-1] @ Trans2
    return Trans1

@ray.remote
def step2_parallel(f, start, end, dimt, tMatij_n, tMatij_np1, hij):
    ret = np.ones_like(tMatij_np1[(f)-1, start:end])
    for j in range(start, end):
        Trans4 = np.zeros((dimt, dimt), dtype=dtype)
        for i in range (1, f):
            Trans4 += hij[(f)-1, (i)-1] @ tMatij_n[(i)-1, (j)-1]
        ret[(j)-start] = tMatij_np1[(f)-1, (f)-1] @ Trans4
    return (start, end, ret)

@ray.remote 
def step3_parallel(hij, tMatij_n, tMatij_np1, f, f_start, f_end, dimt, dtype):
    ret = np.ones_like(tMatij_np1[f_start: f_end, :f])
    for k in range(f_start, f_end):
        for i in range (1, f + 1):
            Trans1 = np.zeros((dimt, dimt), dtype=dtype)
            for j in range (1, f):
                Trans1 +=  tMatij_n[(k)-1, (j)-1] @ hij[(j)-1, (f)-1]

            ret[(k)-f_start, (i)-1] = Trans1 @ tMatij_np1[(f)-1, (i)-1]
            if i != f:
                ret[(k)-f_start, (i)-1] += tMatij_n[(k)-1, (i)-1]
    return (f_start, f_end, ret)

@ray.remote
def step4_parallel(f, start, end, dimt, tMatij_n, tMatij_np1, hij):
    ret = np.ones_like(tMatij_np1[start:end, (f)-1])
    for k in range(start, end):
        Trans4 = np.zeros((dimt, dimt), dtype=dtype)
        for j in range (1, f):
            Trans4 += hij[(k)-1, (j)-1] @ tMatij_n[(j)-1, (f)-1]
        ret[(k)-start] = Trans4 @ tMatij_np1[(f)-1, (f)-1]
    return (start, end, ret)


def rctma(num, nmax, lbd, nmat, configuration, num_workers=1):

    nbp = num
    dimt = 2 * nmax * (nmax + 2)

    # Compute vscatter
    # vscatterer[(f)-1]: nf*nf
    vscatterer = sm.VScatterer(nmax, lbd, nmat, configuration)

    # hij[findice(j,f)]: nj*nf
    hij_file = open("external/data/H.npy", "rb")
    hij = pickle.load(hij_file)
    hij_id = ray.put(hij)

    tMatij_n = np.zeros((nbp, nbp, dimt, dimt), dtype=dtype)
    # [[0 for i in range(nbp)] for j in range(nbp)]

    tMatij_np1 = np.zeros((nbp, nbp, dimt, dimt), dtype=dtype)

    # ========================================================================
    # CALCULATION OF THE TWO FIRST RELATION : 2 PARTICLES SYSTEM (N=2)
    # ========================================================================

    # T [(1,1) 2]
    Trans1 = vscatterer[(2)-1] @ hij[(2)-1, (1)-1]
    Trans2 = hij[(1)-1, (2)-1] @ Trans1
    Trans1 = vscatterer[(1)-1] @ Trans2
    Trans2 = np.linalg.inv(np.identity(dimt) - Trans1)
    tMatij_n[(1)-1, (1)-1] = Trans2 @ vscatterer[(1)-1]
     
    # ETAPE 2: CALCUL DE LA MATRICE T [(1,2) 2]
    # ========================================================================
    tMatij_n[(1)-1, (2)-1] = tMatij_n[(1)-1, (1)-1] @ hij[(1)-1, (2)-1] @ vscatterer[(2)-1] 
     
    # ETAPE 3: CALCUL DE LA MATRICE T [(2,2) 2]
    # ========================================================================
    Trans1 = vscatterer[(2)-1] @ hij[(2)-1, (1)-1] @ vscatterer[(1)-1] @ hij[(1)-1, (2)-1]
    Trans2 = np.linalg.inv(np.identity(dimt) - Trans1)
    tMatij_n[(2)-1, (2)-1] = Trans2 @ vscatterer[(2)-1]

    # ETAPE 4: CALCUL DE LA MATRICE T [(2,1) 2]
    # ========================================================================
    tMatij_n[(2)-1, (1)-1] = tMatij_n[(2)-1, (2)-1] @ hij[(2)-1, (1)-1] @ vscatterer[(1)-1] 

    if nbp < 2:
        raise ValueError
    if nbp == 2:
        return tMatij_n

    # ===========================================================================
    # ===========================================================================
    #     	GENERAL CASE WHEN N > 2
    # ===========================================================================
    # ===========================================================================

    for f in range(3, nbp + 1):
        # ===========================================================================
        #      			CALCULATION OF THE FIRST RELATION N1
        # ===========================================================================

        stride = round(f / num_workers)

        # STEP 1: CALCUL DE LA MATRICE T (f,f) f
        # =======================================

        Trans1 = np.zeros((dimt, dimt), dtype=dtype)
        tMatij_n_id = ray.put(tMatij_n)

        futures = []
        for f_start in range(1, f, stride):
            f_end = min(f_start + stride, f)
            Trans2 = step1_parallel.remote(hij_id, tMatij_n_id, f, f_start, f_end, dimt, dtype)
            futures.append(Trans2)

        results = ray.get(futures)
        for result in results:
            Trans1 = Trans1 + result

        Trans3 = vscatterer[(f)-1] @ Trans1
        Trans4 = np.linalg.inv(np.identity(Trans3.shape[0]) - Trans3)

        tMatij_np1[(f)-1, (f)-1] = Trans4 @ vscatterer[(f)-1]

        # ===========================================================================
        #    			CALCULATION OF THE RELATION N2
        # ===========================================================================

        # ETAPE 2:CALCULATION OF THE MATRICES T (N,k) N with k different from N
        # ===========================================================================
        futures = []
        tMatij_n_id = ray.put(tMatij_n)
        tMatij_np1_id = ray.put(tMatij_np1)
        for start in range(1, f, stride):
            end = min(start+stride, f)
            ret = step2_parallel.remote(f, start, end, dimt, tMatij_n_id, tMatij_np1_id, hij_id)
            futures.append(ret)

        results = ray.get(futures)
        for result in results:
            start, end, ret = result
            tMatij_np1[(f)-1, start-1:end-1] = np.copy(ret)

        # ===========================================================================
        #     			CALCULATION OF THE RELATION N3			   
        # ===========================================================================

        # ETAPE 3: CALCULATION OF THE MATRICES T (j,k) N with k different from N
        # ===========================================================================
        tMatij_n_id = ray.put(tMatij_n)
        tMatij_np1_id = ray.put(tMatij_np1)

        futures = []
        for f_start in range(1, f, stride):
            f_end = min(f_start + stride, f)
            ret = step3_parallel.remote(hij_id, tMatij_n_id, tMatij_np1_id, f, f_start, f_end, dimt, dtype)
            futures.append(ret)

        results = ray.get(futures)

        for result in results:
            f_start, f_end, array = result
            tMatij_np1[f_start - 1:f_end - 1, :f] = np.copy(array)

        # ===========================================================================
        #     			CALCULATION OF THE RELATION N4
        # ===========================================================================
            
        # Calculation of the matrices T (j,N) N with k = N
        # ===========================================================================

        futures = []
        tMatij_n_id = ray.put(tMatij_n)
        tMatij_np1_id = ray.put(tMatij_np1)
        for start in range(1, f, stride):
            end = min(start+stride, f)
            ret = step4_parallel.remote(f, start, end, dimt, tMatij_n_id, tMatij_np1_id, hij_id)
            futures.append(ret)

        results = ray.get(futures)
        for result in results:
            start, end, ret = result
            tMatij_np1[start-1:end-1, (f)-1] = np.copy(ret)

        # for k in range(1, f):
        #     Trans4 = np.zeros((dimt, dimt), dtype=dtype)
        #     for j in range(1, f):
        #         Trans4 += tMatij_n[k-1, j-1] @ hij[j-1, f-1]
        #     tMatij_np1[k-1, f-1] = Trans4 @ tMatij_np1[f-1, f-1]

        # Preparation of the new recurrence
        # ===========================================================================
        tMatij_n = np.copy(tMatij_np1)
        
    return tMatij_n

if __name__ == "__main__":
    import pickle
    
    test_num = 1
    config_num = {1: 9, 2: 14, 3:10, 4: 9, 5: 13, 6:3}
    num = config_num[test_num]
    nmax = 6

    dimt = 2 * nmax * (nmax + 2)
    IN_FILE = "InputDataC{}.txt".format(test_num)

    time0 = time.time()

    redis_password = "123456"
    num_workers = 3
    os.environ["ip_head"] = '10.214.97.24:6379'
    # ray.init(num_cpus = num_workers)
    ray.init(address=os.environ["ip_head"], redis_password=redis_password)
    print(ray.nodes())


    time1 = time.time()
    print("time to initialize ray:", time1 - time0)
    lbd, n0, particles = parameter_parser(nmax, IN_FILE)
    tMatij_n = rctma(num, nmax, lbd, n0, particles, num_workers)
    time2 = time.time()
    print("time to run rctma:", time2 - time1)
