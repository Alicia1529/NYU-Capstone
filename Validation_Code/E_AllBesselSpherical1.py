# e_AllBesselSpherical1(n,z)

import numpy as np
import scipy.special as sp

# Spherical Bessel function of the first kind j_n(n, z)
def bessel1(n, z):
    return sp.spherical_jn(n, z)

# Spherical Bessel function of the second kind y_n(n,z)
def bessel2(n, z):
    return sp.spherical_yn(n, z)

# Spherical Hankel function of the first kind h1_n(z)
def bessel3(n, z):
    return sp.spherical_jn(n,z) + 1.j * sp.spherical_yn(n,z)

# Spherical Hankel function of the second kind h2_n(z)
def bessel4(n, z):
    return sp.spherical_jn(n,z) - 1.j * sp.spherical_yn(n,z)

# Derivative Spherical Bessel function of the first kind dj_n(z)
def bessel5(n, z):
    return sp.spherical_jn(n, z, derivative=True)

# Derivative Spherical Bessel function of the second kind dy_n(z)
def bessel6(n, z):
    return sp.spherical_yn(n, z, derivative=True)

# Derivative Spherical Hankel function of the first kind dh1_n(z)
def bessel7(n, z):
    if n == 0:
        return sp.spherical_jn(n, z, derivative=True) + 1.j * sp.spherical_yn(n, z, derivative=True)
    else:
        h11 = sp.spherical_jn(n-1,z) + 1.j*sp.spherical_yn(n-1,z)
        h12 = sp.spherical_jn(n+1,z) + 1.j*sp.spherical_yn(n+1,z)
        return (1./(2*n+1)) * (n*h11-(n+1)*h12)

# Derivative Spherical Hankel function of the first kind dh1_n(z)
def bessel8(n, z):
    if n == 0:
        return sp.spherical_jn(n,z,derivative=True) - 1.j*sp.spherical_yn(n,z,derivative=True)
    else:
        h21 = sp.spherical_jn(n-1,z) - 1.j*sp.spherical_yn(n-1,z)
        h22 = sp.spherical_jn(n+1,z) - 1.j*sp.spherical_yn(n+1,z)
        return (1./(2*n+1)) * (n*h21-(n+1)*h22)

if __name__ == "__main__":
    print("""
    Bessel Functions
    ----------------
    nmax   :   14
    dim    :    8
    z      :    1.800000000e+00    1.000000000e-01
    ----------------""")
    print("   No             re(jn)             im(jn)             re(yn)             im(yn)            re(hn1)            im(hn1)            re(hn2)            im(hn2)")

    nmax = 15
    z = 1.8+0.1j

    for n in range(nmax):
        # Spherical Bessel function of the first kind j_n(n, z)
        j_n = sp.spherical_jn(n,z)
        assert bessel1(n, z) == j_n
        # Spherical Bessel function of the second kind y_n(n,z)
        y_n = sp.spherical_yn(n,z)
        assert bessel2(n, z) == y_n
        # Spherical Hankel function of the first kind h1_n(z)
        h1_n = sp.spherical_jn(n,z) + 1.j*sp.spherical_yn(n,z)
        assert bessel3(n, z) == h1_n
        # Spherical Hankel function of the second kind h2_n(z)
        h2_n = sp.spherical_jn(n,z) - 1.j*sp.spherical_yn(n,z)
        assert bessel4(n, z) == h2_n

        print("{:>5}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}"
            .format(n, j_n.real, j_n.imag, y_n.real, y_n.imag,
                    h1_n.real, h1_n.imag, h2_n.real, h2_n.imag)
            )

    print("\n")
    print("   No             re(jn)             im(jn)             re(yn)             im(yn)            re(hn1)            im(hn1)            re(hn2)            im(hn2)")
    for n in range(nmax):
        # Derivative Spherical Bessel function of the first kind dj_n(z)
        dj_n = sp.spherical_jn(n,z,derivative=True)
        assert bessel5(n, z) == dj_n
        # Derivative Spherical Bessel function of the second kind dy_n(z)
        dy_n = sp.spherical_yn(n,z,derivative=True)
        assert bessel6(n, z) == dy_n

        # Derivative Spherical Hankel function of the first kind dh1_n(z)
        if n == 0:
            dh1_n = sp.spherical_jn(n,z,derivative=True) + 1.j*sp.spherical_yn(n,z,derivative=True)
        else:
            h11 = sp.spherical_jn(n-1,z) + 1.j*sp.spherical_yn(n-1,z)
            h12 = sp.spherical_jn(n+1,z) + 1.j*sp.spherical_yn(n+1,z)
            dh1_n = (1./(2*n+1)) * (n*h11-(n+1)*h12)
        assert bessel7(n, z) == dh1_n

        # Derivative Spherical Hankel function of the first kind dh1_n(z)
        # bessf(8,i) = (1.0/(2.0*i+1.0)) * (i*bessf(4,i-1)-(i+1.0)*bessf(4,i+1)) ;
        if n == 0:
            dh2_n = sp.spherical_jn(n,z,derivative=True) - 1.j*sp.spherical_yn(n,z,derivative=True)
        else:
            h21 = sp.spherical_jn(n-1,z) - 1.j*sp.spherical_yn(n-1,z)
            h22 = sp.spherical_jn(n+1,z) - 1.j*sp.spherical_yn(n+1,z)
            dh2_n = (1./(2*n+1)) * (n*h21-(n+1)*h22)
        assert bessel8(n, z) == dh2_n

        print("{:>5}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}"
            .format(n, dj_n.real, dj_n.imag, dy_n.real, dy_n.imag,
                    dh1_n.real, dh1_n.imag, dh2_n.real, dh2_n.imag)
            )

    print("Pass all the tests!!!!!")
