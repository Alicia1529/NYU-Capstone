
import numpy as np
import scipy.special as sp

import E_AllBesselSpherical1 as e1
import E_AllBesselSpherical2 as e2

# int nn, double lambda, cdouble nmat, cListe cindex, dListe xvalue
def SphericalTMatrix(nn, lbd, nmat, cindex, xvalue):
    # int           n,m,indice
    # double          k0
	# cdouble f1n,f1d,f2n,f2d
	# cdouble k0m, k1
	# cdouble k0r1, k1r1 , f1, f2
	# Affectation
	# ===========
	nmax = nn
	dimtn  = 2 * nmax * (nmax + 2)

	# Size parameters
	# ===============
	k0 = 2.0 * np.pi / lbd
	k0m = k0 * nmat
	k1 = k0 * cindex
	k0r1 = k0m * xvalue
	k1r1 = k1 * xvalue
	
	# Calcul des fonctions de Bessel
	# ==============================
	# BesselSpherical bk0r1 
	# BesselSpherical bk1r1 ;                        
	# bk0r1.e_AllBesselSpherical2 (nmax, k0r1) ;
	# bk1r1.e_AllBesselSpherical2 (nmax, k1r1) ;
	
	# Calcul des coefficients de la matrice
	# =====================================
	
	indice = 0
	
	# tmatrice = cDMatrice(dimtn)
	
	for n in range(1, nmax + 1):
		f1n = k1  * e2.bessel1(n, k0r1) * e2.bessel5(n, k1r1) - k0m * e2.bessel5(n, k0r1) * e2.bessel1(n, k1r1)
		f1d = k0m * e2.bessel7(n, k0r1) * e2.bessel1(n, k1r1) - k1  * e2.bessel3(n, k0r1) * e2.bessel5(n, k1r1)
		f1  = f1n / f1d
		
		f2n = k1  * e2.bessel5(n, k0r1) * e2.bessel1(n, k1r1) - k0m * e2.bessel1(n, k0r1) * e2.bessel5(n, k1r1)
		f2d = k0m * e2.bessel3(n, k0r1) * e2.bessel5(n, k1r1) - k1  * e2.bessel7(n, k0r1) * e2.bessel1(n, k1r1)
		f2 = f2n / f2d
		indice += 1
		print("_i {} n {} f1 {}, f2 {}".format(indice, n, f1, f2))
		# for m in range(n, -n-1, -1):
    	# 	indice += 1
        # 	# tmatrice[indice] = f1
        # 	# tmatrice[indice+dimtn//2] = f2

if __name__ == "__main__":
    SphericalTMatrix(15, 0.5, 1.5, 1.8+0.1j,0.25)
    '''
	nmax : 
	15
	Wavelength (micrometers) : 
	0.5
	Re(nmat) : 
	1.5
	radius
	0.25
	Re (nincl) : Im (ninc)
	1.8
	0.1


	SphericalTMatrix          
	--------------------------
	nmax    :    15
	dimtn   :   510
	--------------------------
	'''