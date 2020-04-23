import time
import numpy as np
import multiprocessing as mp

def rctma(num):

    n1 = 1
    n2 = 2
    nbp = num
    # vscatterer[(f)-1]: nf*nf
    vscatterer = [np.ones((n + 1, n + 1)) for n in range(nbp)]

    # hij[findice(j,f)]: nj*nf
    hij = [[np.random.rand(j + 1, i + 1) for i in range(nbp)] for j in range(nbp)]

    tMatij_n = [[0 for i in range(nbp)] for j in range(nbp)]

    tMatij_np1 = [[0 for i in range(nbp)] for j in range(nbp)]

    # ========================================================================
    # CALCULATION OF THE TWO FIRST RELATION : 2 PARTICLES SYSTEM (N=2)
    # ========================================================================

    # T [(1,1) 2]
    Trans1 = vscatterer[(1)-1] @ hij[(1)-1][(2)-1] @ vscatterer[(2)-1] @ hij[(2)-1][(1)-1]
    Trans2 = np.linalg.inv(np.identity(n1) - Trans1)
    tMatij_n[(1)-1][(1)-1] = Trans2 @ vscatterer[(1)-1]
     
    # ETAPE 2: CALCUL DE LA MATRICE T [(1,2) 2]
    # ========================================================================
    tMatij_n[(1)-1][(2)-1] = tMatij_n[(1)-1][(1)-1] @ hij[(1)-1][(2)-1] @ vscatterer[(2)-1] 
     
    # ETAPE 3: CALCUL DE LA MATRICE T [(2,2) 2]
    # ========================================================================
    Trans1 = vscatterer[(2)-1] @ hij[(2)-1][(1)-1] @ vscatterer[(1)-1] @ hij[(1)-1][(2)-1]
    Trans2 = np.linalg.inv(np.identity(n2) - Trans1)
    tMatij_n[(2)-1][(2)-1] = Trans2 @ vscatterer[(2)-1]

    # ETAPE 4: CALCUL DE LA MATRICE T [(2,1) 2]
    # ========================================================================
    tMatij_n[(2)-1][(1)-1] = tMatij_n[(2)-1][(2)-1] @ hij[(2)-1][(1)-1] @ vscatterer[(1)-1] 

    if nbp < 2:
        raise ValueError
    if nbp == 2:
        return tMatij_n
    # ===========================================================================
    # ===========================================================================
    #     	GENERAL CASE WHEN N > 2
    # ===========================================================================
    # ===========================================================================

    def step1(f, i, shape1, shape2, tMatij_n, hij, send_end):
        Trans2 = np.zeros((shape1, shape2))
        for j in range(1, f):
            Trans2 += tMatij_n[(i)-1][(j)-1] @ hij[(j)-1][(f)-1]
        send_end.send(hij[(f)-1][(i)-1] @ Trans2)

    def step2(f, j, shape1, shape2, tMatij_n, tMatij_np1, hij, send_end):
        Trans4 = np.zeros((vscatterer[(f)-1].shape[0], vscatterer[(j)-1].shape[0]))
        for i in range (1, f):
            Trans4 += hij[(f)-1][(i)-1] @ tMatij_n[(i)-1][(j)-1]
        update = tMatij_np1[(f)-1][(f)-1] @ Trans4
        send_end.send([j, update])

    for f in range(3, nbp + 1):
        # ===========================================================================
        #      			CALCULATION OF THE FIRST RELATION N1
        # ===========================================================================

        # STEP 1: CALCUL DE LA MATRICE T (f,f) f
        # =======================================
        Trans1 = np.zeros((vscatterer[(f)-1].shape[0], vscatterer[(f)-1].shape[0]))

        procs = []
        pipes = []
        for i in range(1, f):
            shape1 = vscatterer[(i)-1].shape[0]
            shape2 = vscatterer[(f)-1].shape[0]
            recv_end, send_end = mp.Pipe(False)
            p = mp.Process(target=step1, args=(f, i, shape1, shape2, tMatij_n, hij, send_end, ))
            procs.append(p)
            pipes.append(recv_end)
            p.start()
            p.join()

        for p in pipes:
            Trans1 += p.recv()
        
        Trans3 = vscatterer[(f)-1] @ Trans1
        Trans4 = np.linalg.inv(np.identity(Trans3.shape[0]) - Trans3)

        tMatij_np1[(f)-1][(f)-1] = Trans4 @ vscatterer[(f)-1]

        # ===========================================================================
        #    			CALCULATION OF THE RELATION N2
        # ===========================================================================

        # ETAPE 2:CALCULATION OF THE MATRICES T (N,k) N with k different from N
        # ===========================================================================

        # for j in range (1, f):
        #     Trans4 = np.zeros((vscatterer[(f)-1].shape[0], vscatterer[(j)-1].shape[0]))
        #     for i in range (1, f):
        #         Trans4 += hij[(f)-1][(i)-1] @ tMatij_n[(i)-1][(j)-1]

        #     tMatij_np1[(f)-1][(j)-1] = tMatij_np1[(f)-1][(f)-1] @ Trans4

        procs = []
        pipes = []
        for j in range(1, f):
            shape1 = vscatterer[(f)-1].shape[0]
            shape2 = vscatterer[(j)-1].shape[0]
            recv_end, send_end = mp.Pipe(False)
            p = mp.Process(target=step2, args=(f, j, shape1, shape2, tMatij_n, tMatij_np1, hij, send_end, ))
            procs.append(p)
            pipes.append(recv_end)
            p.start()
            p.join()

        for p in pipes:
            recv = p.recv()
            tMatij_np1[(f)-1][recv[0]-1] = recv[1]
    
        # ===========================================================================
        #     			CALCULATION OF THE RELATION N3			   
        # ===========================================================================

        # ETAPE 3: CALCULATION OF THE MATRICES T (j,k) N with k different from N
        # ===========================================================================

        for k in range (1, f):
            for i in range (1, f + 1):
                Trans1 = np.zeros((vscatterer[(k)-1].shape[0], vscatterer[(f)-1].shape[0]))
                for j in range (1, f):
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
                Trans4 += tMatij_n[k-1][j-1] @ hij[j-1][f-1]
            tMatij_np1[k-1][f-1] = Trans4 @ tMatij_np1[f-1][f-1]

        # Preparation of the new recurrence
        # ===========================================================================
        for i in range(1, f+1):
            for j in range(1, f+1):
                tMatij_n[i-1][j-1] = tMatij_np1[i-1][j-1]
        print()

time1 = time.time()
rctma(20)
time2 = time.time()
print("time:", time2 - time1)