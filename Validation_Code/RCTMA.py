# why inverse info
# order of multiplication

# Trans4 = cMatrice(vscatterer[(f)-1].g_dimtn(),
# vscatterer[(f)-1].g_dimtn() );

# how to initialize tMatij_np1 and tMatij_n

import time
import numpy as np
from copy import deepcopy


def rctma(num):

    n1 = 1
    n2 = 2
    nbp = num
    # vscatterer[(f)-1]: nf*nf
    vscatterer = [np.ones((n + 1, n + 1)) for n in range(nbp)]

    # hij[findice(j,f)]: nj*nf
    hij = [[np.random.rand(j + 1, i + 1) for i in range(nbp)] for j in range(nbp)]

    # hij = [[np.random.rand(n1, n1), np.random.rand(n1, n2)], # (n1, nf)
    #        [np.random.rand(n2, n1), np.random.rand(n2, n2)]]

    tMatij_n = [[0 for i in range(nbp)] for j in range(nbp)]

    tMatij_np1 = [[0 for i in range(nbp)] for j in range(nbp)]

    # ========================================================================
    # CALCULATION OF THE TWO FIRST RELATION : 2 PARTICLES SYSTEM (N=2)
    # ========================================================================

    # T [(1,1) 2]
    # Trans1 = vscatterer[(2)-1] * hij[findice(2,1)].g_PointerToMatrix() //2*2 x 2*1 ->2*1
    # Trans2 = hij[findice(1,2)] * Trans1 // 1*2 x 2*1 = 1*1
    # Trans1 = vscatterer[(1)-1] * Trans2 // n1*n1 
    Trans1 = vscatterer[(1)-1] @ hij[(1)-1][(2)-1] @ vscatterer[(2)-1] @ hij[(2)-1][(1)-1]
    # Trans2.s_MatUmoinsB(Trans1)
    # Trans2.selfInvertMatrix(info) // n1*n1
    Trans2 = np.linalg.inv(np.identity(n1) - Trans1)
    # tMatij_n[findice(1,1)] = Trans2 * vscatterer[(1)-1] // n1*n1
    tMatij_n[(1)-1][(1)-1] = Trans2 @ vscatterer[(1)-1]
     
    # ETAPE 2: CALCUL DE LA MATRICE T [(1,2) 2]
    # ========================================================================
    # Trans1 =  hij[findice(1,2)].g_PointerToMatrix() * vscatterer[(2)-1] ;
    # tMatij_n[findice(1,2)] = tMatij_n[findice(1,1)] * Trans1 ;
    tMatij_n[(1)-1][(2)-1] = tMatij_n[(1)-1][(1)-1] @ hij[(1)-1][(2)-1] @ vscatterer[(2)-1] 
     
    # ETAPE 3: CALCUL DE LA MATRICE T [(2,2) 2]
    # ========================================================================
    # dim: n1*n1 * n1*n2 = n1*n2
    # Trans1 = vscatterer[(1)-1] * hij[findice(1,2)].g_PointerToMatrix() ;
    # dim: n2*n1 * n1*n2 = n2*n2
    # Trans2 = hij[findice(2,1)] * Trans1 ;
    # dim: n2*n2 * n2*n2 = n2*n2
    # Trans1 = vscatterer[(2)-1] * Trans2 ;  ???
    Trans1 = vscatterer[(2)-1] @ hij[(2)-1][(1)-1] @ vscatterer[(1)-1] @ hij[(1)-1][(2)-1]
    # calcul de I-mat: dim: n2*n2
    # Trans2.s_MatUmoinsB(Trans1) ;
    # Inversion de la matrice: n2*n2
    # Trans2.selfInvertMatrix    (info) ;  ???
    Trans2 = np.linalg.inv(np.identity(n2) - Trans1)
    # dim: n2*n2 * n2*n2 = n2*n2
    # tMatij_n[findice(2,2)] = Trans2 * vscatterer[(2)-1] ;
    tMatij_n[(2)-1][(2)-1] = Trans2 @ vscatterer[(2)-1]

    # ETAPE 4: CALCUL DE LA MATRICE T [(2,1) 2]
    # ========================================================================

    # dim: n2*n1 * n1*n1 = n2*n1
    # Trans1 = hij[findice(2,1)].g_PointerToMatrix() * vscatterer[(1)-1]
    # dim: n2*n2* * n2*n1 = n2*n1
    # tMatij_n[findice(2,1)] = tMatij_n[findice(2,2)] * Trans1 ;
    tMatij_n[(2)-1][(1)-1] = tMatij_n[(2)-1][(2)-1] @ hij[(2)-1][(1)-1] @ vscatterer[(1)-1] 

    # print("0,0", tMatij_n[0][0].shape, tMatij_n[0][0])
    # print("0,1", tMatij_n[0][1].shape, tMatij_n[0][1])
    # print("1,0", tMatij_n[1][0].shape, tMatij_n[1][0])
    # print("1,1", tMatij_n[1][1].shape, tMatij_n[1][1])
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

        # Trans4 = cMatrice(vscatterer[(f)-1].g_dimtn(),
        # vscatterer[(f)-1].g_dimtn() );
        Trans1 = np.zeros((vscatterer[(f)-1].shape[0], vscatterer[(f)-1].shape[0])) # ???
        for i in range(1, f):
            Trans2 = np.zeros((vscatterer[(i)-1].shape[0], vscatterer[(f)-1].shape[0]))
            for j in range(1, f):
                # print("i loop", "i - 1", i - 1, "j - 1", j - 1, "f - 1",f - 1)
                Trans2 += tMatij_n[(i)-1][(j)-1] @ hij[(j)-1][(f)-1]
            Trans1 += hij[(f)-1][(i)-1] @ Trans2
        
        Trans3 = vscatterer[(f)-1] @ Trans1
        Trans4 = np.linalg.inv(np.identity(Trans3.shape[0]) - Trans3)

        tMatij_np1[(f)-1][(f)-1] = Trans4 @ vscatterer[(f)-1]

        # ===========================================================================
        #    			CALCULATION OF THE RELATION N2
        # ===========================================================================

        # ETAPE 2:CALCULATION OF THE MATRICES T (N,k) N with k different from N
        # ===========================================================================

        # for (int j=1; j<=f-1; j++	)	{
        for j in range (1, f):
            # Trans4 = cMatrice (vscatterer[(f)-1].g_dimtn(),
            # vscatterer[(j)-1].g_dimtn() )
            Trans4 = np.zeros((vscatterer[(f)-1].shape[0], vscatterer[(j)-1].shape[0]))
            for i in range (1, f):
                Trans4 += hij[(f)-1][(i)-1] @ tMatij_n[(i)-1][(j)-1]

            tMatij_np1[(f)-1][(j)-1] = tMatij_np1[(f)-1][(f)-1] @ Trans4
    
        # ===========================================================================
        #     			CALCULATION OF THE RELATION N3			   
        # ===========================================================================

        # ETAPE 3: CALCULATION OF THE MATRICES T (j,k) N with k different from N
        # ===========================================================================

        for k in range (1, f):
            for i in range (1, f + 1):
                Trans1 = np.zeros((vscatterer[(k)-1].shape[0], vscatterer[(f)-1].shape[0]))
                for j in range (1, f):
                    # print("f", f,"k", k,"i", i)
                    # print("tMatij_n[(k)-1][(j)-1]", tMatij_n[(k)-1][(j)-1].shape,
                    #     "hij[(j)-1][(f)-1]", hij[(j)-1][(f)-1].shape, "Trans1", Trans1.shape)
                    Trans1 +=  tMatij_n[(k)-1][(j)-1] @ hij[(j)-1][(f)-1]

                if i == f:
                    tMatij_np1[(k)-1][(f)-1] = Trans1 @ tMatij_np1[(f)-1][(f)-1]
                else:
                    Trans2 = Trans1 @ tMatij_np1[(f)-1][(i)-1]
                    tMatij_np1[(k)-1][(i)-1] = tMatij_n[(k)-1][(i)-1] + Trans2

        # ===========================================================================
        #     			CALCULATION OF THE RELATION N4
        # ===========================================================================
            
        # Calculation of the matrices T (j,N) N with k = N
        # ===========================================================================

        for k in range(1, f):
            Trans4 = np.zeros((vscatterer[(k)-1].shape[0], vscatterer[(f)-1].shape[0]))
            for j in range(1, f):
                # print("tMatij_n[k-1][j-1]", tMatij_n[k-1][j-1].shape, )
                Trans4 += tMatij_n[k-1][j-1] @ hij[j-1][f-1]
            tMatij_np1[k-1][f-1] = Trans4 @ tMatij_np1[f-1][f-1]

        # Preparation of the new recurrence
        # ===========================================================================
        for i in range(1, f+1):
            for j in range(1, f+1):
                tMatij_n[i-1][j-1] = tMatij_np1[i-1][j-1]

time1 = time.time()
rctma(40)
time2 = time.time()
print("time:", time2 - time1)