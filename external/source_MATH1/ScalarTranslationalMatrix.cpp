/*
 *  scalarTranslationalMatrix.cpp
 *  iTECHS
 *
 *  Created by Jean Claude Auger on 16/07/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

// En-tete des classes ANSI MSL C++
// ================================


// En-tete des classes personnelles
// ================================
#include "ScalarTranslationalMatrix.h"
#include "AssociatedLegendreFunction.h"
#include "TableauX.h"
#include "BesselSpherical.h" 
#include "Matrice.h"

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::ScalarTranslationalMatrix::ScalarTranslationalMatrix()
// ======================================================
{
//   cout<<"CONSTRUCTEUR  ScalarTranslationalMatrix 1 "<<endl;

   nmax   = 1 ;
   numax  = 1 ;
   kd0    = 1.0 ;
   theta0 = 0.0 ;
   phi0   = 0.0 ;
   
   dimn   = nmax *(nmax +2) ;
   dimnu  = numax*(numax+2) ;
   sm = cTableau (0,dimn,0,dimnu) ;
   for (int i=0;i<dimFactorielMax;i++) ffac[i]=fa(i) ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::ScalarTranslationalMatrix::ScalarTranslationalMatrix
		(int i, int j, cdouble z, double t, double p)
// =============================================================================
{
 //  cout<<"CONSTRUCTEUR  ScalarTranslationalMatrix 2 "<<endl;
   nmax   = i ;
   numax  = j ;
   kd0    = z ;
   theta0 = t ;
   phi0   = p ;
   
   dimn   = nmax *(nmax +2) ;
   dimnu  = numax*(numax+2) ;
   sm = cTableau (0,dimn,0,dimnu) ;
	for (int ii=0;ii<dimFactorielMax;ii++) ffac[ii]=fa(ii) ;
 }

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::ScalarTranslationalMatrix::ScalarTranslationalMatrix
		(const ScalarTranslationalMatrix& lsm)
// =============================================================================
{
//   cout<<"CONSTRUCTEUR  RECOPIE ScalarTranslationalMatrix  "<<endl;
   nmax   = lsm.nmax ;
   numax  = lsm.numax ;
   kd0    = lsm.kd0 ;
   theta0 = lsm.theta0 ;
   phi0   = lsm.phi0 ;
   
   dimn   = lsm.dimn ;
   dimnu  = lsm.dimnu ;
   sm = lsm.sm ;
   for (int i=0;i<dimFactorielMax;i++) ffac[i]=lsm.ffac[i] ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=


// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::ScalarTranslationalMatrix& math1::ScalarTranslationalMatrix
        ::operator= (const ScalarTranslationalMatrix& lsm)
// =============================================================================
{
if  (this !=&lsm)
    {
    nmax   = lsm.nmax ;
    numax  = lsm.numax ;
    kd0    = lsm.kd0 ;
    theta0 = lsm.theta0 ;
    phi0   = lsm.phi0 ;
   
    dimn   = lsm.dimn ;
    dimnu  = lsm.dimnu ;
    sm = lsm.sm ;
    for (int i=0;i<dimFactorielMax;i++) ffac[i]=lsm.ffac[i] ;
    }
   	return *this ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::ScalarTranslationalMatrix::~ScalarTranslationalMatrix ()
// ========================================================
{
//   cout<<"DESTRUCTEUR  ScalarTranslationalMatrix "<<endl;

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::ScalarTranslationalMatrix::s_AttributeTo
		(int n, int nu, cdouble z, double t, double p)
// =============================================================================
{
    nmax   = n  ;
    numax  = nu ;
    kd0    = z  ;
    theta0 = t  ;
    phi0   = p  ;
 }

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::ScalarTranslationalMatrix :: c_Ynm 
		(int ordrem, double theta1, double phi1, 
		 Matrice<cdouble > &lYnumu)
// =============================================================================
{
// =======================	
int             lm     ;
double          x1,x2,pi ;
double zero5 = 0.5 ;
cdouble z1       ;
// =======================
AssociatedLegendreFunction leg ;
leg.e_AllFunctions(ordrem, theta0) ;	

pi = 4.0 * atan(1.0) ;

    for (int n=0;n<=ordrem;n++)
		 for (int m=n;m>=-n;m--)	{ 
			 lm = abs(m) ;

			 x1 =  fa(n-lm)*(2.0*double(n)+1.0)/(4.0*pi*fa(n+lm)) ; 
			 x2 = pow(x1,zero5) ;
			 z1 = x2  * leg(1,n,lm) *cdouble(cos(lm*phi0),sin(lm*phi0)) ;
			 if (m>=0) 
				 lYnumu(n*n+n-m+1) = z1 ;
			 else
				 lYnumu(n*n+n-m+1) = conj(z1)*mun(lm) ;
		 }
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

  void math1::ScalarTranslationalMatrix 
			:: e_BetaMatrix (TranslationTheoremAlgorithm i)
// =============================================================================
{

switch (i)	{
	case chewRecursif:
		c_BetaMatrixChewRecursif () ;	
		break ;
	case brian3Y:
		c_BetaMatrixBrian3Y () ;
		break ;
}

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

  void math1::ScalarTranslationalMatrix
			:: e_AlphaMatrix (TranslationTheoremAlgorithm i)
// =============================================================================
{

switch (i)	{
	case chewRecursif:
		c_AlphaMatrixChewRecursif () ;	
		break ;
	case brian3Y:
		c_AlphaMatrixBrian3Y () ;
		break ;
}

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

  void math1::ScalarTranslationalMatrix
			:: c_3Y0BrianRecurrence (TableauX<double> &t3Y0)
// =============================================================================
{
int n,m,nu,mu ;
double r1, r2, r3 ;
double pi = 4.0*atan(1.0) ;

// Etape 1: calcul des 3Y0 (n,m,0,0) - Eq.48 Document Brian
// ========================================================
for (n=0;n<=nmax;n++)
{
for (m=n;m>=-n;m--)
{
t3Y0(n*n+n-m,0) = 0.5/sqrt(pi) ;
}
}


// Etape 2: calcul des 3Y0 (n,m,nu,-nu) - Eq.50 Document Brian
// ===========================================================
for (n=0;n<=nmax;n++)
{
for (m=n;m>=-n;m--)
{
for (nu=1;nu<=numax;nu++)
{
r1 = double( (2.0*nu+1.0)*(n+2.0*nu+m)*(n+2.0*nu+m-1) ) ;
r2 = double(  2.0*nu*(2.0*n+2.0*nu+1.0)*(2.0*n+2.0*nu-1.0) ) ;
r3 = sqrt(r1/r2) ;

t3Y0(n*n+n-m,nu*nu+nu+nu) = -r3*t3Y0(n*n+n-m,(nu-1)*(nu-1)+(nu-1)+(nu-1))  ;
}
}
}

// Etape 3: calcul des 3Y0 (n,m,nu,mu) - Eq.51 Document Brian
// ===========================================================
for (n=0;n<=nmax;n++)
{
for (m=n;m>=-n;m--)
{
for (nu=1;nu<=numax;nu++)
{
for (mu=-(nu-1);mu<=nu;mu++)
{
r1 = double((n+nu-m+mu)*(nu-mu+1)) ;
r2 = double((n+nu+m-mu+1)*(nu+mu)) ;
r3 = sqrt(r1/r2) ;
t3Y0(n*n+n-m,nu*nu+nu-mu) = -r3*t3Y0(n*n+n-m,nu*nu+nu-(mu-1)) ;
}
}
}
}



}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

  double math1::ScalarTranslationalMatrix
			  :: c_3Y0BrianAvecFactoriel (int n, int m, int nu, int mu)
// =============================================================================
{
double tY0 ;
double r1,r2,r3,r4 ;
double pi=4.0*atan(1.0) ;

r1 = mun(mu)/2.0/sqrt(pi)   ;
r1 = r1*ffac[2*n] /ffac[n]  ;
r1 = r1*ffac[2*nu]/ffac[nu] ;
r1 = r1*ffac[n+nu]/ffac[2*n+2*nu] ;

r2 = sqrt (double((2.0*n+1.0)*(2.0*nu+1.0)/(2.0*n+2.0*nu+1.0))) ;

r3 = ffac[n+nu-m+mu]/ffac[n+m]/ffac[n-m] ;
r3 = r3 * ffac[n+nu+m-mu]/ffac[nu+mu]/ffac[nu-mu] ;
r4 = sqrt(r3) ;

return tY0=r1*r2*r4 ;
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

  void math1::ScalarTranslationalMatrix::c_3YBrian
      (int n, int m, int nu, int mu, int qmax, TableauX<double> &t3Yq)
// =============================================================================
{
int n4,q,k,kmin,kmax ;
double r1,r2,r3  ;

n4 = n + nu + m - mu ;

// Etape 1: Calcul des Aq0 et Aqk - Eq.76 et 79 Document Brian
// ============================================================
TableauX<double> Aqq(0,qmax,0,qmax) ;
Aqq (0,0) = 1.0 ;

for (q=1;q<=qmax;q++)
{
r1 = double((n4-2.0*q+2.0)*(n4-2.0*q+1.0))/double(2.0*q)/double(2.0*n+2.0*nu-2.0*q+1.0) ;
Aqq (q,0) = -1.0*r1*Aqq(q-1,0) ;
//cout<<"Aq0  "<<q<<"  "<<Aqq(q,0)<<endl ;

for (k=1;k<=q;k++)
{
r1 = double ( (2.0*(n+nu)-4.0*k+1.0)*(n+nu-2.0*k+2.0-m+mu)*(n+nu-2.0*k+1.0-m+mu) ) ;
r2 = double ( (2.0*(n+nu)-4.0*k+5.0)*(n+nu-2.0*k+2.0+m-mu)*(n+nu-2.0*k+1.0+m-mu) ) ;
r3 = sqrt (r1/r2) * double(2.0*(k-q-1.0))/double((2.0*n+2.0*nu-2.0*q-2.0*k+1))     ;
//cout <<q<<"  "<<r1<<"  "<<r2<<endl ;
Aqq (q,k) = Aqq(q,k-1)*r3 ;
//cout<<"Aqq  "<<k<<"  "<<q<<"  "<<Aqq(q,k)<<endl ;
}
}



// Etape 2: Calcul des bqq et bqk - Eq.67 et 68 Document Brian
// ============================================================
TableauX<double> bqq(0,qmax,0,qmax) ;
bqq (0,0) = 1.0 ;
for (q=1;q<=qmax;q++)
{
r1 = double( (n+m-2.0*q+2.0)*(n+m-2.0*q+1.0)) ;
r2 = double (2.0*q*(2.0*n-2.0*q+1.0)) ;
r3 = -r1/r2 ;
bqq(q,q) = r3* bqq(q-1,q-1) ;
}

for (k=0;k<qmax;k++)
{
for (q=k+1;q<=qmax;q++)
{
r1 = double((nu-mu-2.0*q+2.0*k+2.0)*(nu-mu-2.0*q+2.0*k+1.0)) ;
r2 = double(2.0*(q-k)*(2.0*nu-2.0*q+2.0*k+1.0)) ;
r3 = -r1/r2 ;
bqq(q,k) = r3* bqq(q-1,k) ;
}
}
// Etape 3: Calcul des Bq - Eq. 65 Document Brian
// ===============================================
TableauX<double> Bq(0,qmax) ;

Bq(0) = 1.0 ;

for (q=1;q<=qmax;q++)
{
kmin = max (0,q-int((nu-mu)/2)) ;
kmax = min (q,  int((n+m)  /2))     ;
Bq(q) = 0.0 ;
for (k=kmin;k<=kmax;k++)  Bq(q) = Bq(q) + bqq(q,k) ;
}

// Etape 4: Calcul des 3Yq - Eq. 80 Document Brian
// ===============================================
t3Yq(0) = Bq(0)/Aqq(0,0) ;
for (q=1;q<=qmax;q++)
{
r1 = 0.0 ;
for (k=0;k<=q-1;k++) r1 = r1 + Aqq(q,k)*t3Yq(k) ;
t3Yq(q) = (Bq(q)-r1)/Aqq(q,q) ;
}
 
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

  void math1::ScalarTranslationalMatrix :: c_BetaMatrixBrian3Y ()
// =============================================================================
{
int n,m,nu,mu,q,qmax,qmax1 ;
int ordre,i,j,p ;
double pi=4.0*atan(1.0) ;
TableauX<double> mat3Yq ;

//cout<< "c_BetaMatrixBrian3Y IN "<<endl ;

// Etape 1: Dimension de la Matrice Beta de passage
// =================================================
   dimn  =  nmax  *(nmax +2) ;
   dimnu =  numax *(numax +2) ;
   sm = cTableau (0,dimn,0,dimnu) ;

// Etape 1: Calcul des harmoniques spheriques scalaires
// ====================================================
   ordre = nmax+numax+1 ;
   Matrice<cdouble > Ynumu(ordre*(ordre+2)+1,1) ;
   c_Ynm (ordre, theta0, phi0, Ynumu) ;

// Etape 2: Calcul des fonctions de Bessel Jn
// ==========================================
   BesselSpherical besj ;
   besj.e_Jn(ordre, kd0) ;

// Etape 3: Calcul des coefficients 3Y0 par recurrence
// ===================================================
TableauX<double> t3Y0(0,dimn,0,dimnu) ;
c_3Y0BrianRecurrence (t3Y0) ;

// Etape 4: Boucle sur les coefficients de la Matrice Beta de passage
// ==================================================================
for (n=0;n<=nmax;n++)	{
	for (m=n;m>=-n;m--)	{ 
		for (nu=0;nu<=numax;nu++)	{
			for (mu=nu;mu>=-nu;mu--)
			{
				i = n*n+n-m     ;
				j = nu*nu+nu-mu ;
				// Calcul des coefficients normalisés 3Yq
				// ======================================
				qmax1 = min(n,nu)                        ;
				qmax  = min(qmax1,int((n+nu-abs(m-mu))/2))    ;
				mat3Yq.changeDimensionTo (0,qmax) ;
				c_3YBrian (n,m,nu,mu,qmax,mat3Yq) ;
				sm(i,j) = cdouble(0.0,0.0)      ;
				for (q=0;q<=qmax;q++)	{
					p = n+nu-2*q ;
					if (abs(m-mu)<=p)	{
						sm(i,j) = sm(i,j) + ipn(p) * besj(1,p) * Ynumu(p*p+p-(m-mu)+1) * mat3Yq(q)  ;
					}
//cout <<setw(6)<< n <<" "<<setw(6)<< m <<" "<<setw(6)<< nu <<setw(6)<< mu <<" "<<setw(6)<< q<<" "<<setw(6)<< qmax
// <<"  "<<setw(19)<< mat3Yq(q)<<endl ;
				}
				sm(i,j) = sm(i,j)*4.0*pi*ipn(nu-n)*t3Y0(i,j) ;
			}
		}
	}
}


}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

  void math1::ScalarTranslationalMatrix :: c_AlphaMatrixBrian3Y ()
// =============================================================================
{
int n,m,nu,mu,q,qmax,qmax1 ;
int ordre,i,j,p ;
double pi=4.0*atan(1.0) ;
TableauX<double> mat3Yq ;

//cout<< "c_BetaMatrixBrian3Y IN "<<endl ;

// Etape 1: Dimension de la Matrice Beta de passage
// =================================================
   dimn  =  nmax  *(nmax +2) ;
   dimnu =  numax *(numax +2) ;
   sm = cTableau (0,dimn,0,dimnu) ;

// Etape 1: Calcul des harmoniques spheriques scalaires
// ====================================================
   ordre = nmax+numax+1 ;
   Matrice<cdouble > Ynumu(ordre*(ordre+2)+1,1) ;
   c_Ynm (ordre, theta0, phi0, Ynumu) ;
	
/*	
	cout<<"Ynumu"<<endl ;
	cout<<Ynumu<<endl ;
*/	

// Etape 2: Calcul des fonctions de Bessel Jn
// ==========================================
   BesselSpherical besj ;
   besj.e_Hn(ordre, kd0) ;

// Etape 3: Calcul des coefficients 3Y0 par recurrence
// ===================================================
TableauX<double> t3Y0(0,dimn,0,dimnu) ;
c_3Y0BrianRecurrence (t3Y0) ;

// Etape 4: Boucle sur les coefficients de la Matrice Beta de passage
// ==================================================================
for (n=0;n<=nmax;n++)	{
	for (m=n;m>=-n;m--)	{ 
		for (nu=0;nu<=numax;nu++)	{
			for (mu=nu;mu>=-nu;mu--)	{
				i = n*n+n-m     ;
				j = nu*nu+nu-mu ;
				// Calcul des coefficients normalisés 3Yq
				// ======================================
				qmax1 = min(n,nu)                        ;
				qmax  = min(qmax1,int((n+nu-abs(m-mu))/2))    ;
				mat3Yq.changeDimensionTo(0,qmax) ;
				c_3YBrian (n,m,nu,mu,qmax,mat3Yq) ;
				sm(i,j) = cdouble(0.0,0.0)      ;

				for (q=0;q<=qmax;q++)	{
					p = n+nu-2*q ;
					if (abs(m-mu)<=p)	{
						sm(i,j) = sm(i,j) + ipn(p) * besj(3,p) * Ynumu(p*p+p-(m-mu)+1) * mat3Yq(q)  ;
					}
//cout <<setw(6)<< n <<" "<<setw(6)<< m <<" "<<setw(6)<< nu <<setw(6)<< mu <<" "<<setw(6)<< q<<" "<<setw(6)<< qmax
// <<"  "<<setw(19)<< mat3Yq(q)<<endl ;
				}
				sm(i,j) = sm(i,j)*4.0*pi*ipn(nu-n)*t3Y0(i,j) ;
			}
		}
	}
}


}



// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

  void math1::ScalarTranslationalMatrix :: c_BetaMatrixChewRecursif ()
// =============================================================================
{
double pi=4.0*atan(1.0) ;
int n,nu,m,mu ;
int indice_nu ;
int indice_n  ;
int ordre ;
cdouble y ;


// Etape 0: Definition de la Matrice Beta de passage
// =================================================
   dimn  =  nmax *(nmax +2) ;
   dimnu = (nmax+numax+1) * (nmax+numax+3) ;
   cTableau sm1 ;
   sm1 = cTableau (0,dimn,0,dimnu) ;
   sm = cTableau (0,dimn,0,dimnu) ;

// Etape 1: Calcul des harmoniques spheriques scalaires
// ====================================================
   ordre = nmax+numax+1 ;
   Matrice<cdouble > Ynumu(ordre*(ordre+2)+1,1) ;
   c_Ynm (ordre, theta0, phi0, Ynumu) ;
 //  Ynumu.showObjectValues () ;

// Etape 2: Calcul des fonctions de Bessel Jn
// ==========================================
   BesselSpherical besJ ;
   besJ.e_Jn(ordre, kd0) ;
//   besJ.showObjectValues () ;

// Etape 3: Calculs des termes Beta (nu,mu,0,0)
// ============================================
double zero5 = 0.5 ;
   n = 0 ;
   m = 0 ;
   for (nu=0 ; nu <= nmax+numax+1 ; nu++)
   for (mu=nu; mu >= -nu          ; mu--)
       {
       indice_nu = nu*nu + nu - mu ;
       sm1(0,indice_nu) = Ynumu(nu*nu+nu+mu+1) * mun (nu+mu) * pow(4.0*pi,zero5) * besJ(1,nu) ;	
	   }


//sm1.showObjectValues () ; //cout<<"Etape 3 Ok "<<endl ;
// cin >> attente ;
 

// Etape 4 : Calculs des Beta (nu,mu,n=m,m) from Recur_Eq26
// ========================================================

  for (n=1;n<=nmax;n++)
  {
  m = n ;
  for (nu=0;nu<=nmax+numax+1-n;nu++)
  {
  for (mu=nu;mu>=-nu;mu--)
  {
  indice_nu = nu*nu + nu - mu ;
  indice_n  = n*n ;

    y = cdouble(0.0,0.0) ;
    if ( abs(mu-1) <= abs(nu-1) && abs(m-1) <= abs(n-1) && (nu-1) >=0 && (n-1) >= 0)
    y = y + bplus(nu-1,mu-1) * sm1((n-1)*(n-1)+(n-1)-(m-1),(nu-1)*(nu-1)+(nu-1)-(mu-1)) ;

    if ( abs(mu-1) <= abs(nu+1) && abs(m-1) <= abs(n-1) && (nu+1) >=0 && (n-1) >=0)
    y = y + bmoins(nu+1,mu-1) * sm1((n-1)*(n-1)+(n-1)-(m-1),(nu+1)*(nu+1)+(nu+1)-(mu-1)) ;

    sm1(indice_n,indice_nu) = y / bplus(n-1,m-1) ;
//	if (n<=nmax && nu<=numax ) sm(indice_n,indice_nu) = sm1(indice_n,indice_nu) ;    
   }
   }
   }
// cout<<"Etape 4 Ok "<<endl ;
// cin >> attente ; 

// Etape 5 :Calcul de Beta (nu,mu,n) from Recur_Eq23
// =================================================
   for (n=1;n<=nmax;n++)
   for (m=n-1;m>=0;m--)
   for (nu=0;nu<=nmax+numax;nu++)
   for (mu=nu;mu>=-nu;mu--)
   {
   indice_nu = nu * nu + nu - mu ;
   indice_n  = n * n + n - m ;

    y = cdouble(0.0,0.0) ;

    if ( abs(mu) <= abs(nu) && abs(m) <= abs(n-2) && (n-2) >= 0 && nu >= 0 )
    y = y - amoins(n-1,m) * sm1((n-2)*(n-2)+(n-2)-m,nu*nu+nu-mu) ;

    if ( abs(mu) <= abs(nu-1) && abs(m) <= abs(n-1) && (nu-1) >=0 && (n-1) >= 0) 
    y = y + aplus(nu-1,mu) * sm1((n-1)*(n-1)+(n-1)-m,(nu-1)*(nu-1)+(nu-1)-mu) ;

    if ( abs(mu) <= abs(nu+1) && abs(m) <= abs(n-1) && (nu+1) >=0 && (n-1) >=0) 
    y = y + amoins(nu+1,mu) * sm1((n-1)*(n-1)+(n-1)-m,(nu+1)*(nu+1)+(nu+1)-mu) ;

    sm1(indice_n,indice_nu) = y / aplus(n-1,m) ;
//	if (n<=nmax && nu<=numax ) sm(indice_n,indice_nu) = sm1(indice_n,indice_nu) ;    
}

// cout<<"Etape 5 Ok "<<endl ;
 //cin >> attente ; 


// Etape 6 : Evaluation of the terns with negative m 
// =================================================
for (nu=0;nu<=numax;nu++)
for (mu=nu;mu>=-nu;mu--)
for (n=1;n<=nmax;n++)
for (m=1;m<=n;m++)
{
sm1 (n*n+n+m,nu*nu+nu-mu) =  mun(m+mu)      * conj(sm1(n*n+n-m,nu*nu+nu+mu))	;
//sm(n*n+n+m,nu*nu+nu-mu) =  sm1 (n*n+n+m,nu*nu+nu-mu)	;
}

sm = sm1 ;

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

  void math1::ScalarTranslationalMatrix ::c_AlphaMatrixChewRecursif ()
// =============================================================================
{
double pi=4.0*atan(1.0) ;
int n,nu,m,mu ;
int indice_nu ;
int indice_n  ;
int ordre ;
cdouble y ;

// Etape 0: Definition de la Matrice Beta de passage
// =================================================
   dimn  =  nmax *(nmax +2) ;
   dimnu = (nmax+numax+1) * (nmax+numax+3) ;
   cTableau sm1,sm2 ;
   sm1 = cTableau (0,dimn,0,dimnu) ;
   sm2 = cTableau (0,dimn,0,dimnu) ;
   sm = cTableau (0,dimn,0,dimnu) ;

// Etape 1: Calcul des harmoniques spheriques scalaires
// ====================================================
   ordre = nmax+numax+1 ;
   Matrice<cdouble > Ynumu(ordre*(ordre+2)+1,1) ;
   c_Ynm (ordre, theta0,phi0,Ynumu) ;

// Etape 2: Calcul des fonctions de Bessel Jn
// ==========================================
   BesselSpherical besH;
   besH.e_Hn(ordre, kd0) ;


// Etape 3: Calculs des termes Beta (nu,mu,0,0)
// ============================================
  n = 0 ;
  m = 0 ;
  for (nu=0 ; nu <= nmax+numax+1 ; nu++)
  {
  for (mu=nu; mu >= -nu          ; mu--)
  {
   indice_nu = nu*nu + nu - mu ;
   sm1(0,indice_nu) = Ynumu(nu*nu+nu+mu+1) * mun (nu+mu) * sqrt(4.0*pi) * besH(3,nu)             ;
   sm2(0,indice_nu) = Ynumu(nu*nu+nu+mu+1) * mun (nu+mu) * sqrt(4.0*pi) * conj(besH(3,nu)) * mun(nu+1) ;	
   if (n<=nmax && nu<=numax ) sm(0,indice_nu) = sm1(0,indice_nu) ;    
  }
  }
// Etape 4 : Calculs des Beta (nu,mu,n=m,m) from Recur_Eq26
// ========================================================

  for (n=1;n<=nmax;n++)
  {
  m = n ;
  for (nu=0;nu<=nmax+numax+1-n;nu++)
  {
  for (mu=nu;mu>=-nu;mu--)
  {
  indice_nu = nu*nu + nu - mu ;
  indice_n  = n*n ;

    y = cdouble(0.0,0.0) ;
    if ( abs(mu-1) <= abs(nu-1) && abs(m-1) <= abs(n-1) && (nu-1) >=0 && (n-1) >= 0)
    y = y + bplus(nu-1,mu-1) * sm1((n-1)*(n-1)+(n-1)-(m-1),(nu-1)*(nu-1)+(nu-1)-(mu-1)) ;

    if ( abs(mu-1) <= abs(nu+1) && abs(m-1) <= abs(n-1) && (nu+1) >=0 && (n-1) >=0)
    y = y + bmoins(nu+1,mu-1) * sm1((n-1)*(n-1)+(n-1)-(m-1),(nu+1)*(nu+1)+(nu+1)-(mu-1)) ;

    sm1(indice_n,indice_nu) = y / bplus(n-1,m-1) ;
    if (n<=nmax && nu<=numax ) sm(indice_n,indice_nu) = sm1(indice_n,indice_nu) ;    

    y = cdouble(0.0,0.0) ;
    if ( abs(mu-1) <= abs(nu-1) && abs(m-1) <= abs(n-1) && (nu-1) >=0 && (n-1) >= 0)
    y = y + bplus(nu-1,mu-1) * sm2((n-1)*(n-1)+(n-1)-(m-1),(nu-1)*(nu-1)+(nu-1)-(mu-1)) ;

    if ( abs(mu-1) <= abs(nu+1) && abs(m-1) <= abs(n-1) && (nu+1) >=0 && (n-1) >=0)
    y = y + bmoins(nu+1,mu-1) * sm2((n-1)*(n-1)+(n-1)-(m-1),(nu+1)*(nu+1)+(nu+1)-(mu-1)) ;

    sm2(indice_n,indice_nu) = y / bplus(n-1,m-1) ;
    
   }
   }
   }

// Etape 5 :Calcul de Beta (nu,mu,n) from Recur_Eq23
// =================================================
   for (n=1;n<=nmax;n++)
   for (m=n-1;m>=0;m--)
   for (nu=0;nu<=nmax+numax;nu++)
   for (mu=nu;mu>=-nu;mu--)
   {
   indice_nu = nu * nu + nu - mu ;
   indice_n  = n * n + n - m ;

    y = cdouble(0.0,0.0) ;

    if ( abs(mu) <= abs(nu) && abs(m) <= abs(n-2) && (n-2) >= 0 && nu >= 0 )
    y = y - amoins(n-1,m) * sm1((n-2)*(n-2)+(n-2)-m,nu*nu+nu-mu) ;

    if ( abs(mu) <= abs(nu-1) && abs(m) <= abs(n-1) && (nu-1) >=0 && (n-1) >= 0) 
    y = y + aplus(nu-1,mu) * sm1((n-1)*(n-1)+(n-1)-m,(nu-1)*(nu-1)+(nu-1)-mu) ;

    if ( abs(mu) <= abs(nu+1) && abs(m) <= abs(n-1) && (nu+1) >=0 && (n-1) >=0) 
    y = y + amoins(nu+1,mu) * sm1((n-1)*(n-1)+(n-1)-m,(nu+1)*(nu+1)+(nu+1)-mu) ;

    sm1(indice_n,indice_nu) = y / aplus(n-1,m) ;
   if (n<=nmax && nu<=numax ) sm(indice_n,indice_nu) = sm1(indice_n,indice_nu) ;    

    
    y = cdouble(0.0,0.0) ;

    if ( abs(mu) <= abs(nu) && abs(m) <= abs(n-2) && (n-2) >= 0 && nu >= 0 )
    y = y - amoins(n-1,m) * sm2((n-2)*(n-2)+(n-2)-m,nu*nu+nu-mu) ;

    if ( abs(mu) <= abs(nu-1) && abs(m) <= abs(n-1) && (nu-1) >=0 && (n-1) >= 0) 
    y = y + aplus(nu-1,mu) * sm2((n-1)*(n-1)+(n-1)-m,(nu-1)*(nu-1)+(nu-1)-mu) ;

    if ( abs(mu) <= abs(nu+1) && abs(m) <= abs(n-1) && (nu+1) >=0 && (n-1) >=0) 
    y = y + amoins(nu+1,mu) * sm2((n-1)*(n-1)+(n-1)-m,(nu+1)*(nu+1)+(nu+1)-mu) ;

    sm2(indice_n,indice_nu) = y / aplus(n-1,m) ;
   }

// Etape 6 : Evaluation of the terns with negative m 
// =================================================
for (nu=0;nu<=numax;nu++)
for (mu=nu;mu>=-nu;mu--)
for (n=1;n<=nmax;n++)
for (m=1;m<=n;m++)
{
   indice_nu = nu * nu + nu - mu ;
   indice_n  = n * n + n - m ;

sm (n*n+n+m,nu*nu+nu-mu) =    mun(m+mu)         * conj(sm1 (n*n+n-m,nu*nu+nu+mu))	;
 sm2  (n*n+n+m,nu*nu+nu-mu) =  -1.0*mun(m+mu+n+nu) * conj(sm2(n*n+n-m,nu*nu+nu+mu))	;
}

// Etape 7 : Calcul de la matrice Alpha à partir des deux sous-matrices 
// ====================================================================
for (n=0;n<=nmax;n++)
for (m=-1;m>=-n;m--)
for (nu=0;nu<=numax;nu++)
for (mu=nu;mu>=-nu;mu--)

{
	indice_nu = nu * nu + nu - mu ;
	indice_n = n * n + n - m ;

	sm(indice_n,indice_nu) = sm2(indice_n,indice_nu) ;
}
  
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   double math1::ScalarTranslationalMatrix:: aplus (int n,int m)
// ======================================================
{
   double z ;
   z = -1.0*pow ( (n+m+1.0)*(n-m+1.0)/((2.0*n+1.0)*(2.0*n+3.0)),0.5 ) ;
   return z ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   double math1::ScalarTranslationalMatrix:: amoins (int n,int m)
// ======================================================
{
   double z ;
   z = pow ( (n+m)*(n-m)/((2.0*n+1.0)*(2.0*n-1.0)),0.5) ;
   return z ;
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   double math1::ScalarTranslationalMatrix:: bmoins (int n,int m)
// ======================================================
{
   double z ;
   z = pow ( (n-m)*(n-m-1.0)/((2.0*n+1.0)*(2.0*n-1.0)),0.5) ;
   return z ;
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   double math1::ScalarTranslationalMatrix:: bplus (int n,int m)
// ======================================================
{
   double z ;
   z = pow ( (n+m+2.0)*(n+m+1.0)/((2.0*n+1.0)*(2.0*n+3.0)),0.5)  ;
   return z ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

	ostream& math1::operator <<(ostream& stream,ScalarTranslationalMatrix o )
// =========================================================================
{
		stream.precision(9);
		stream << showpoint; 
		stream << setiosflags (ios::scientific);
		
		stream<<endl;
		stream <<"Scalar Translational Matrix"<<endl ;
		stream <<"-----------------------------"<<endl ;
		stream <<"nmax    : "<<setw(5)<<o.nmax <<" "<<setw(5)<<o.dimn <<endl ;
		stream <<"nmax    : "<<setw(5)<<o.numax<<" "<<setw(5)<<o.dimnu<<endl ;
		stream <<"-----------------------------"<<endl ;
		stream <<"kd     : "<<setw(19)<<real(o.kd0)<<" "<<setw(19)<<imag(o.kd0)<<endl;
		stream <<"Theta  : "<<setw(19)<<o.theta0<<endl;
		stream <<"Phi    : "<<setw(19)<<o.phi0  <<endl;
		stream <<"-----------------------------"<<endl ;
		
		int indice_n, indice_nu ;
		
		for (int nu=0;nu<=o.numax;nu++)
			for (int mu=nu;mu>=-nu;mu--)
				for (int n=0;n<=o.nmax;n++)
					for (int m=n;m>=-n;m--)
						
					{
						indice_nu = nu * nu + nu - mu ;
						indice_n = n * n + n - m ;

						cout<<setw(5)<<indice_nu<<"  "
							 <<setw(5)<<indice_n <<"  "
							 <<setw(5)<<nu <<"  "
							 <<setw(5)<<mu <<"  "
							 <<setw(5)<<n  <<"  "
							 <<setw(5)<<m  <<"  "
							 <<setw(19)<<real( o.sm(indice_n,indice_nu) )<<"  "
							 <<setw(19)<<imag( o.sm(indice_n,indice_nu) )<<endl ;
							
						
					}
						
				
		return stream ;	
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::testScalarTranslationalMatrix ()
// =============================================================================
{

	int nmax ;
//	TranslationTheoremAlgorithm tt ;

cout.precision(9);
cout << showpoint; 
cout << setiosflags (ios::scientific);

	cout<<"	Programme LSC : Teste de la class: TestScalarTranslationalMatrix "<<endl ;
	cout<<" ================================================================="<<endl ;
	cout<<" "<<endl ;




// Calcul des coefficients normalisés 3Yq
// ======================================
/*
        ScalarTranslationalMatrix sm1b ;
int qmax1 ;
int qmax ;
		sm1b.setAttributesTo (14, 14, z, t, p) ;
n = 14 ;
m = 5 ;
nu = 8 ;
mu = 3 ;
TableauX<double> mat3Yq ;
qmax1 = min(n,nu)                        ;
qmax  = min(qmax1,int((n+nu-abs(m-mu))/2))    ;
mat3Yq.resize (0,qmax) ;
sm1b.c_3YBrian (n,m,nu,mu,qmax,mat3Yq) ;

for (q=0;q<=qmax;q++)
cout <<q<<"   "<<mat3Yq(q)<<endl ; ;

*/
	ScalarTranslationalMatrix sm1b ;

	cdouble z ;
	double t, p ;
	
	z = cdouble (2.0,0.0) ;
	t = 4.0*atan(1.0) ;
	p = 0.0 ;
	nmax = 2 ;

	sm1b.s_AttributeTo (nmax, nmax, z, t, p) ;
	sm1b.e_AlphaMatrix (brian3Y) ; 
	cout<<sm1b<<endl ;
		
	t = 0.0 ;
	sm1b.s_AttributeTo (nmax, nmax, z, t, p) ;
	sm1b.e_AlphaMatrix (brian3Y) ; 
	cout<<sm1b<<endl ;
	
		
//		Matrice<cdouble > Ynumu(ordre*(ordre+2)+1,1) ;
//		sm1bCalculateYnm (ordre, theta0, phi0, Ynumu) ;

		
		
		
		
		
 //       sm1b.showObjectValues () ;
//		tt = brian3Y ;
//		tt = chewRecursif ;

//        ScalarTranslationalMatrix sm2b ;
//		nmax = 2 ;
//		sm2b.setAttributesTo (nmax, nmax, z, t, p) ;	
//		tt = chewRecursif ;
//		sm2b.e_BetaMatrix (tt) ; 
//		sm2b.showObjectValues () ;
//		sm1b.e_AlphaMatrix (1) ; 
//		sm1b.showObjectValues () ;
//		sm2b=sm1b ;
//				sm2b.showObjectValues () ;

  //sm1b.c_BetaMatrixBrian3Y () ;

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=



