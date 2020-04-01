# e_AllBesselSpherical2(n,z)

import numpy as np
import scipy.special as sp

# Spherical Bessel function of the first kind j_n(n, z)
def bessel1(n, z):
    return z * sp.spherical_jn(n,z)

# Spherical Bessel function of the second kind y_n(n,z)
def bessel2(n, z):
    return z * sp.spherical_yn(n, z)

# Spherical Hankel function of the first kind h1_n(z)
def bessel3(n, z):
    return z * (sp.spherical_jn(n,z) + 1.j * sp.spherical_yn(n,z))

# Spherical Hankel function of the second kind h2_n(z)
def bessel4(n, z):
    return z * (sp.spherical_jn(n,z) - 1.j * sp.spherical_yn(n,z))

# Derivative Spherical Bessel function of the first kind dj_n(z)
def bessel5(n, z):
    return sp.spherical_jn(n,z) + z * sp.spherical_jn(n,z,derivative=True)

# Derivative Spherical Bessel function of the second kind dy_n(z)
def bessel6(n, z):
    return sp.spherical_yn(n,z) + z * sp.spherical_yn(n,z,derivative=True)

# Derivative Spherical Hankel function of the first kind dh1_n(z)
def bessel7(n, z):
    h1_n = sp.spherical_jn(n,z) + 1.j*sp.spherical_yn(n,z)
    if n == 0:
        dh1_n = sp.spherical_jn(n,z,derivative=True) + 1.j*sp.spherical_yn(n,z,derivative=True)
        zdh1_n = h1_n + z * dh1_n
    else:
        h11 = sp.spherical_jn(n-1,z) + 1.j*sp.spherical_yn(n-1,z)
        h12 = sp.spherical_jn(n+1,z) + 1.j*sp.spherical_yn(n+1,z)
        dh1_n = (1./(2*n+1)) * (n*h11-(n+1)*h12)
        zdh1_n = h1_n + z * dh1_n
    return zdh1_n

# Derivative Spherical Hankel function of the first kind dh1_n(z)
def bessel8(n, z):
    h2_n = sp.spherical_jn(n,z) - 1.j*sp.spherical_yn(n,z)
    if n == 0:
        dh2_n = sp.spherical_jn(n,z,derivative=True) - 1.j*sp.spherical_yn(n,z,derivative=True)
        zdh2_n = h2_n + z * dh2_n
    else:
        h21 = sp.spherical_jn(n-1,z) - 1.j*sp.spherical_yn(n-1,z)
        h22 = sp.spherical_jn(n+1,z) - 1.j*sp.spherical_yn(n+1,z)
        dh2_n = (1./(2*n+1)) * (n*h21-(n+1)*h22)
        zdh2_n = h2_n + z * dh2_n
    return zdh2_n

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
        zj_n = z * sp.spherical_jn(n,z)
        assert bessel1(n, z) == zj_n
        # Spherical Bessel function of the second kind y_n(n,z)
        zy_n = z * sp.spherical_yn(n,z)
        assert bessel2(n, z) == zy_n
        # Spherical Hankel function of the first kind h1_n(z)
        zh1_n = z * (sp.spherical_jn(n,z) + 1.j*sp.spherical_yn(n,z))
        assert bessel3(n, z) == zh1_n
        # Spherical Hankel function of the second kind h2_n(z)
        zh2_n = z * (sp.spherical_jn(n,z) - 1.j*sp.spherical_yn(n,z))
        assert bessel4(n, z) == zh2_n

        print("{:>5}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}"
            .format(n, zj_n.real, zj_n.imag, zy_n.real, zy_n.imag,
                    zh1_n.real, zh1_n.imag, zh2_n.real, zh2_n.imag)
            )

    print("\n")
    print("   No             re(jn)             im(jn)             re(yn)             im(yn)            re(hn1)            im(hn1)            re(hn2)            im(hn2)")
    for n in range(nmax):
        # Derivative Spherical Bessel function of the first kind dj_n(z)
        zdj_n = sp.spherical_jn(n,z) + z * sp.spherical_jn(n,z,derivative=True)
        assert bessel5(n, z) == zdj_n
        # Derivative Spherical Bessel function of the second kind dy_n(z)
        zdy_n = sp.spherical_yn(n,z) + z * sp.spherical_yn(n,z,derivative=True)
        assert bessel6(n, z) == zdy_n

        # Derivative Spherical Hankel function of the first kind dh1_n(z)
        h1_n = sp.spherical_jn(n,z) + 1.j*sp.spherical_yn(n,z)
        if n == 0:
            dh1_n = sp.spherical_jn(n,z,derivative=True) + 1.j*sp.spherical_yn(n,z,derivative=True)
            zdh1_n = h1_n + z * dh1_n
        else:
            h11 = sp.spherical_jn(n-1,z) + 1.j*sp.spherical_yn(n-1,z)
            h12 = sp.spherical_jn(n+1,z) + 1.j*sp.spherical_yn(n+1,z)
            dh1_n = (1./(2*n+1)) * (n*h11-(n+1)*h12)
            zdh1_n = h1_n + z * dh1_n
        assert bessel7(n, z) == zdh1_n

        # Derivative Spherical Hankel function of the first kind dh1_n(z)
        # bessf(8,i) = (1.0/(2.0*i+1.0)) * (i*bessf(4,i-1)-(i+1.0)*bessf(4,i+1)) ;
        h2_n = sp.spherical_jn(n,z) - 1.j*sp.spherical_yn(n,z)
        if n == 0:
            dh2_n = sp.spherical_jn(n,z,derivative=True) - 1.j*sp.spherical_yn(n,z,derivative=True)
            zdh2_n = h2_n + z * dh2_n
        else:
            h21 = sp.spherical_jn(n-1,z) - 1.j*sp.spherical_yn(n-1,z)
            h22 = sp.spherical_jn(n+1,z) - 1.j*sp.spherical_yn(n+1,z)
            dh2_n = (1./(2*n+1)) * (n*h21-(n+1)*h22)
            zdh2_n = h2_n + z * dh2_n
        assert bessel8(n, z) == zdh2_n

        print("{:>5}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}{:>19.9e}"
            .format(n, zdj_n.real, zdj_n.imag, zdy_n.real, zdy_n.imag,
                    zdh1_n.real, zdh1_n.imag, zdh2_n.real, zdh2_n.imag)
            )

    print("Pass all the tests!!!!!")
