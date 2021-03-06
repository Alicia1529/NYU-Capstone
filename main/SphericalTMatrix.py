
import numpy as np
import scipy.special as sp

import E_AllBesselSpherical1 as e1
import E_AllBesselSpherical2 as e2

# nmax, wavelength, nmat, nincl, radius
def SphericalTMatrix(nn, lbd, nmat, xvalue, cindex_re, cindex_im):
	# Affectation
	# ===========
	nmax = nn
	dimtn  = 2 * nmax * (nmax + 2)
	cindex = cindex_re + cindex_im * 1.j

	# Size parameters
	# ===============
	k0 = 2.0 * np.pi / lbd
	k0m = k0 * nmat
	k1 = k0 * cindex
	k0r1 = k0m * xvalue
	k1r1 = k1 * xvalue
	
	# tmatrice = cDMatrice(dimtn)
	tmatrice = np.empty(dimtn, dtype=complex)
	
	indice = 0
	for n in range(1, nmax+1):
		f1n = k1  * e2.bessel1(n, k0r1) * e2.bessel5(n, k1r1) - k0m * e2.bessel5(n, k0r1) * e2.bessel1(n, k1r1)
		f1d = k0m * e2.bessel7(n, k0r1) * e2.bessel1(n, k1r1) - k1  * e2.bessel3(n, k0r1) * e2.bessel5(n, k1r1)
		f1  = f1n / f1d
		
		f2n = k1  * e2.bessel5(n, k0r1) * e2.bessel1(n, k1r1) - k0m * e2.bessel1(n, k0r1) * e2.bessel5(n, k1r1)
		f2d = k0m * e2.bessel3(n, k0r1) * e2.bessel5(n, k1r1) - k1  * e2.bessel7(n, k0r1) * e2.bessel1(n, k1r1)
		f2 = f2n / f2d

		for m in range(n, -n-1, -1):
			tmatrice[indice] = f1
			tmatrice[indice+dimtn//2] = f2
			indice += 1
	return tmatrice


def VScatterer(nn, lbd, nmat, configuration):
	size = configuration.shape[0]
	tmp = []
	dimt = 2 * nn * (nn + 2)
	for i in range(size):
		args = list(configuration[i][3:])
		tmp.append(np.diag(SphericalTMatrix(nn, lbd, nmat, *args)))
	return np.array(tmp)


def validation():
	print('''
nmax : 
25
Wavelength (micrometers) : 
0.555
Re(nmat) : 
1.6
radius
0.632
Re (nincl) : Im (ninc)
2.75
1.72

SphericalTMatrix          
--------------------------
nmax    :    25
dimtn   :  1350
--------------------------
	''')
	
	print("   i_    n    m        re(Tmatrix)        im(Tmatrix)")
	
	nn, lbd, nmat, cindex, xvalue = 25, 0.555, 1.6, 2.75+1.72j, 0.632
	dimtn  = 2 * nn * (nn + 2)
	tmatrix = SphericalTMatrix(nn, lbd, nmat, cindex, xvalue)

	indice = 1
	for n in range(1, nn+1):
		for m in range(n, -n-1, -1):
			print("{:>5}{:>5}{:>5}{:>19.9e}{:>19.9e}"
				.format(indice, n, m, tmatrix[indice-1].real, tmatrix[indice-1].imag)
			)
			indice += 1
	for n in range(1, nn+1):
		for m in range(n, -n-1, -1):
			print("{:>5}{:>5}{:>5}{:>19.9e}{:>19.9e}"
				.format(indice, n, m, tmatrix[indice-1].real, tmatrix[indice-1].imag)
			)
			indice += 1

	print("--------------------------")
	print("   i_    n        re(Tmatrix)        im(Tmatrix)")

	dimtn  = 2 * nn * (nn + 2)

	# Size parameters
	# ===============
	k0 = 2.0 * np.pi / lbd
	k0m = k0 * nmat
	k1 = k0 * cindex
	k0r1 = k0m * xvalue
	k1r1 = k1 * xvalue
	
	indice = 1
	for n in range(1, nn+1):
		f1n = k1  * e2.bessel1(n, k0r1) * e2.bessel5(n, k1r1) - k0m * e2.bessel5(n, k0r1) * e2.bessel1(n, k1r1)
		f1d = k0m * e2.bessel7(n, k0r1) * e2.bessel1(n, k1r1) - k1  * e2.bessel3(n, k0r1) * e2.bessel5(n, k1r1)
		f1  = f1n / f1d
		print("{:>5}{:>5}{:>19.9e}{:>19.9e}"
			.format(indice, n, f1.real, f1.imag)
		)
		indice += 1

	for n in range(1, nn+1):
		f2n = k1  * e2.bessel5(n, k0r1) * e2.bessel1(n, k1r1) - k0m * e2.bessel1(n, k0r1) * e2.bessel5(n, k1r1)
		f2d = k0m * e2.bessel3(n, k0r1) * e2.bessel5(n, k1r1) - k1  * e2.bessel7(n, k0r1) * e2.bessel1(n, k1r1)
		f2 = f2n / f2d
		print("{:>5}{:>5}{:>19.9e}{:>19.9e}"
			.format(indice, n, f2.real, f2.imag)
		)
		indice += 1
						  
if __name__ == "__main__":
	import time
	nmax = 3
	dimtn  = 2 * nmax * (nmax + 2)

	num = 9
	configuration = np.array([[0.000000000e+00,    0.000000000e+00,    0.000000000e+00, 1.000000000e+00, 2.516,              0.120],
							  [0.000000000e+00,    0.000000000e+00,    6.400000000e+00, 1.000000000e+00, 1.625,              0.015],
							  [0.000000000e+00,    0.000000000e+00,   -6.400000000e+00, 1.000000000e+00, 1.625,              0.015],
							  [6.400000000e+00,    0.000000000e+00,    0.000000000e+00, 1.000000000e+00, 1.625,              0.015],
							  [-6.400000000e+00,    0.000000000e+00,    0.000000000e+00, 1.000000000e+00, 1.625,              0.015],
							  [-6.400000000e+00,    0.000000000e+00,    6.400000000e+00, 1.000000000e+00, 1.300,              0.080],
							  [-6.400000000e+00,    0.000000000e+00,   -6.400000000e+00, 1.000000000e+00, 1.300,              0.080],
							  [6.400000000e+00,    0.000000000e+00,    6.400000000e+00, 1.000000000e+00, 1.300,              0.080],
							  [6.400000000e+00,    0.000000000e+00,   -6.400000000e+00, 1.000000000e+00, 1.300,              0.080]])

	lbd = 3.14159265
	nmat = 1.0 
	time_start = time.time()

	# t1 = SphericalTMatrix(nmax, lbd, nmat, *list(configuration[0, 3:]))
	# print(t1.shape)
	# print(t1)

	# vscatterer = VScatterer(nmax, lbd, nmat, configuration)
	# time_end = time.time()
	# print("Total time:", time_end - time_start)
	# print(vscatterer[0])
	# # for i in range(9):
	# # 	print("\nThe " + str(i) + "th T matrix is\n")
	# # 	print(vscatterer[i])
	# # # print(vscatterer.shape)