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

def rctma(num, nmax, lbd, nmat, configuration, num_workers=1):

    nbp = num
    dimt = 2 * nmax * (nmax + 2)

    # Compute vscatter
    # vscatterer[(f)-1]: nf*nf
    vscatterer = sm.VScatterer(nmax, lbd, nmat, configuration)

    # hij[findice(j,f)]: nj*nf
    hij_file = open("external/data/H.npy", "rb")
    hij = pickle.load(hij_file)

    tMatij_n = np.zeros((nbp, nbp, dimt, dimt), dtype=dtype)

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

        # STEP 1: CALCUL DE LA MATRICE T (f,f) f
        # =======================================

        Trans1 = np.zeros((dimt, dimt), dtype=dtype) # ???
        for i in range(1, f):
            Trans2 = np.zeros((dimt, dimt), dtype=dtype)
            for j in range(1, f):
                Trans2 += tMatij_n[(i)-1, (j)-1] @ hij[(j)-1, (f)-1]
            Trans1 += hij[(f)-1, (i)-1] @ Trans2
        
        Trans3 = vscatterer[(f)-1] @ Trans1
        Trans4 = np.linalg.inv(np.identity(Trans3.shape[0]) - Trans3)

        tMatij_np1[(f)-1, (f)-1] = Trans4 @ vscatterer[(f)-1]

        # ===========================================================================
        #    			CALCULATION OF THE RELATION N2
        # ===========================================================================

        # ETAPE 2:CALCULATION OF THE MATRICES T (N,k) N with k different from N
        # ===========================================================================

        for j in range (1, f):
            # Trans4 = cMatrice (vscatterer[(f)-1].g_dimtn(),
            # vscatterer[(j)-1].g_dimtn() )
            Trans4 = np.zeros((dimt, dimt), dtype=dtype)
            for i in range (1, f):
                Trans4 += hij[(f)-1, (i)-1] @ tMatij_n[(i)-1, (j)-1]

            tMatij_np1[(f)-1, (j)-1] = tMatij_np1[(f)-1, (f)-1] @ Trans4
    
        # ===========================================================================
        #     			CALCULATION OF THE RELATION N3			   
        # ===========================================================================

        # ETAPE 3: CALCULATION OF THE MATRICES T (j,k) N with k different from N
        # ===========================================================================

        for k in range (1, f):
            for i in range (1, f + 1):
                Trans1 = np.zeros((dimt, dimt), dtype=dtype)
                for j in range (1, f):
                    Trans1 +=  tMatij_n[(k)-1, (j)-1] @ hij[(j)-1, (f)-1]

                tMatij_np1[(k)-1, (i)-1] = Trans1 @ tMatij_np1[(f)-1, (i)-1]
                if i != f:
                    tMatij_np1[(k)-1, (i)-1] += tMatij_n[(k)-1, (i)-1]

        # ===========================================================================
        #     			CALCULATION OF THE RELATION N4
        # ===========================================================================
            
        # Calculation of the matrices T (j,N) N with k = N
        # ===========================================================================

        for k in range(1, f):
            Trans4 = np.zeros((dimt, dimt), dtype=dtype)
            for j in range(1, f):
                Trans4 += tMatij_n[k-1, j-1] @ hij[j-1, f-1]
            tMatij_np1[k-1, f-1] = Trans4 @ tMatij_np1[f-1, f-1]

        # Preparation of the new recurrence
        # ===========================================================================
        tMatij_n = np.copy(tMatij_np1)
        
    return tMatij_n

if __name__ == "__main__":
    import pickle
    
    test_num = 1
    config_num = {1: 9, 2: 14, 3:10, 4: 9, 5: 13, 6:3}
    num = config_num[test_num]
    nmax = 13

    dimt = 2 * nmax * (nmax + 2)
    IN_FILE = "InputDataC{}.txt".format(test_num)

    time1 = time.time()
    lbd, n0, particles = parameter_parser(nmax, IN_FILE)
    tMatij_n = rctma(num, nmax, lbd, n0, particles)
    time2 = time.time()
    print("time:", time2 - time1)

    
if __name__ == "__main__":
    import pickle
    
    test_num = 1
    config_num = {1: 9, 2: 14, 3:10, 4: 9, 5: 13}
    num = config_num[test_num]
    nmax = 13

    dimt = 2 * nmax * (nmax + 2)
    IN_FILE = "InputDataC{}.txt".format(test_num)

    time1 = time.time()
    lbd, n0, particles = parameter_parser(nmax, IN_FILE)
    tMatij_n = rctma(num, nmax, lbd, n0, particles)
    time2 = time.time()
    print("time:", time2 - time1)
