/*
 *  vectorialTranslationalMatrix.cpp
 *  iTECHS
 *
 *  Created by Jean Claude Auger on 16/07/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

// ANSI MSL C++ classes
// =============================================================================

// Project classes
// =============================================================================
#include "VectorialTranslationalMatrix.h"


// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::VectorialTranslationalMatrix::VectorialTranslationalMatrix()
// ============================================================
{

   nmax   = 0 ;
   numax  = 0 ;
   kd0     = cdouble(0.0,0.0) ;
   theta0 = 0.0 ;
   phi0   = 0.0 ;
   
   dimn   = 1 ;
   dimnu  = 1 ;
   vm = cMatrice (dimn,dimnu) ;
   stm = new ScalarTranslationalMatrix () ;

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::VectorialTranslationalMatrix::VectorialTranslationalMatrix (const VectorialTranslationalMatrix& o)
// ===========================================================================================
{

   nmax   = o.nmax ;
   numax  = o.numax ;
   kd0    = o.kd0  ;
   theta0 = o.theta0 ;
   phi0   = o.phi0 ;
   
   dimn   = o.dimn ;
   dimnu  = o.dimnu ;

   vm = o.vm ;
   stm = new ScalarTranslationalMatrix () ;   
   *stm = *o.stm ;
   Aout = o.Aout ;
   Bout = o.Bout ;

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

math1::VectorialTranslationalMatrix & math1::VectorialTranslationalMatrix:: operator =
   (const VectorialTranslationalMatrix& o)
// =============================================================================
{
 
if  (this !=&o)
       {
   nmax   = o.nmax ;
   numax  = o.numax ;
   kd0     = o.kd0  ;
   theta0 = o.theta0 ;
   phi0   = o.phi0 ;
   dimn   = o.dimn ;
   dimnu  = o.dimnu ;

   vm = o.vm ;
   delete stm;
   stm = new ScalarTranslationalMatrix () ;
   *stm = *o.stm ;
   
   Aout = o.Aout ;
   Bout = o.Bout ;

       }
   return *this ;

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::VectorialTranslationalMatrix::~VectorialTranslationalMatrix ()
// =====================================================================
{
  delete stm ;
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

	void math1::VectorialTranslationalMatrix::e_JMatrix 
		(int i, int j, cdouble z, double t, double p,
		 TranslationTheoremAlgorithm tip)
// =============================================================================
{

	// Etape 1: initialisation de la Matrice J
	// =======================================
	if  (i != nmax || j !=numax)
	{
		nmax   = i ;
		numax  = j ;
		dimn   = 2*nmax *(nmax +2) ;
		dimnu  = 2*numax*(numax+2) ;
		vm = cMatrice (dimn, dimnu) ;
	}
	kd0     = z ;
	theta0  = t ;
	phi0    = p ;
	
	// Etape 2: Calcul de la Matrice de translation scalaire
	// =====================================================
	delete stm ;
	stm = new ScalarTranslationalMatrix ;
	stm->s_AttributeTo(nmax,numax,kd0 ,theta0,phi0) ;
	stm->e_BetaMatrix (tip) ;
		
	// Etape 3: Calcul de la Matrice de translation vectorielle
	// ========================================================
	c_JMatrixMackowskiRecursif () ;

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::VectorialTranslationalMatrix::g_JMatrix 
	(cMatrice&mat1, int i, int j, 
	cdouble z, double t, double p, TranslationTheoremAlgorithm tip)
// =============================================================================
{

	e_JMatrix (i, j, z, t, p, tip) ;
	mat1=vm ;

 }
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::VectorialTranslationalMatrix::c_JMatrixMackowskiRecursif ()
// ==============================================================================
{
int i_n,i_nu ;

// Etape 2: Generation de la Matrice Jij
// =====================================
for (int n=1;n<=nmax;n++)
for (int m=n;m>=-n;m--)
for (int nu=1;nu<=numax;nu++)
for (int mu=nu;mu>=-nu;mu--)
    {
	i_n  = n *n +n -m  ;
	i_nu = nu*nu+nu-mu ;
	c_ABMackowskiWithScalarMatrix (n,m,nu,mu) ;
	vm (i_n,i_nu)   			     = Aout ;
	vm (i_n,i_nu+dimnu/2)        = Bout ;
	vm (i_n+dimn/2,i_nu)         = Bout ;
	vm (i_n+dimn/2,i_nu+dimnu/2) = Aout ;
    }
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::VectorialTranslationalMatrix::g_RgARgBMatrix 
      (cMatrice&vma, cMatrice&vmb, int i,
	   int j, cdouble z, double t, double p,
	   TranslationTheoremAlgorithm tip)
// =============================================================================
{
// Etape 1: initialisation des dimensions et des parametres
// ========================================================
nmax   = i ;
numax  = j ;
dimn   = 2*nmax *(nmax +2) ;
dimnu  = 2*numax*(numax+2) ;
kd0    = z ;
theta0 = t ;
phi0   = p ;

 vma = cMatrice (dimn/2,dimnu/2) ;	 
 vmb = cMatrice (dimn/2,dimnu/2) ;	 

// Etape 2: Calcul de la Matrice de translation scalaire
// =====================================================
    delete stm ;
    stm = new ScalarTranslationalMatrix ;
	 stm->s_AttributeTo(nmax,numax,kd0 ,theta0,phi0) ;
	 stm->e_BetaMatrix (tip) ;

//	 cout<<"g_RgARgBMatrix passage 1 OK "<<endl ;
//	 cout<<*stm ;
//	 cin>>attente ;
// Etape 3: Calcul des coefficients vectoriels de translation
// ==========================================================
int ii,jj ;
for (int n=1;n<=nmax;n++)
for (int m=n;m>=-n;m--)
for (int nu=1;nu<=numax;nu++)
for (int mu=nu;mu>=-nu;mu--)
    {
    ii  = n*n+n-m  ;
	 jj  = nu*nu+nu-mu ;
	c_ABMackowskiWithScalarMatrix (n,m,nu,mu) ;
	vma (ii,jj)   			     = Aout ;
	vmb (ii,jj)   			     = Bout ;
    }
 }
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::VectorialTranslationalMatrix::g_ABMatrix 
       (cMatrice&vma, cMatrice&vmb, int i, 
	    int j, cdouble z, double t, double p, 
		TranslationTheoremAlgorithm tip)
// =============================================================================
{
	// Etape 1: initialisation des dimensions et des parametres
	// ========================================================
	nmax   = i ;
	numax  = j ;
	dimn   = 2*nmax *(nmax +2) ;
	dimnu  = 2*numax*(numax+2) ;
	kd0    = z ;
	theta0 = t ;
	phi0   = p ;
	
	vma = cMatrice (dimn/2,dimnu/2) ;	 
	vmb = cMatrice (dimn/2,dimnu/2) ;	 
	
	// Etape 2: Calcul de la Matrice de translation scalaire
	// =====================================================
	delete stm ;
	stm = new ScalarTranslationalMatrix ;
	stm->s_AttributeTo(nmax,numax,kd0 ,theta0,phi0) ;
	stm->e_AlphaMatrix (tip) ;
	
	//	 cout<<"g_RgARgBMatrix passage 1 OK "<<endl ;
	//	 cout<<*stm ;
	//	 cin>>attente ;
	// Etape 3: Calcul des coefficients vectoriels de translation
	// ==========================================================
	int ii,jj ;
	for (int n=1;n<=nmax;n++)
		for (int m=n;m>=-n;m--)
			for (int nu=1;nu<=numax;nu++)
				for (int mu=nu;mu>=-nu;mu--)
				{
					ii  = n*n+n-m  ;
					jj  = nu*nu+nu-mu ;
					c_ABMackowskiWithScalarMatrix (n,m,nu,mu) ;
					vma (ii,jj)   			     = Aout ;
					vmb (ii,jj)   			     = Bout ;
				}
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::VectorialTranslationalMatrix::
		c_ABMackowskiWithScalarMatrix (int& n,int& m,int& nu,int& mu)
// =============================================================================
{
int i_n, i_nu ;
double x1 ;
cdouble ci = cdouble (0.0,1.0) ;

Aout = cdouble (0.0,0.0) ;
Bout = cdouble (0.0,0.0) ;


// STEP 1 : Evaluation of Amnnumu coefficients from (*stm)  matrix
// ==============================================================
i_nu = nu*nu + nu -mu ;
i_n  = n *n  + n  -m  ;

Aout = Aout + 2.0 * mu * m * (*stm) (i_n,i_nu) ;

//cout<<"A1 Ok"<<endl ;
//cin >> attente ;

if  (abs(mu+1)<=nu && abs(m+1)<=n)
    {
    x1 = pow ( (n-m)*(n+m+1.0)*(nu-mu)*(nu+mu+1.0),0.5 ) ;
    i_nu = nu*nu+nu-(mu+1)                            ;
    i_n  = n*n+n-(m+1)                                ;
    Aout = Aout +  x1 * (*stm) (i_n,i_nu)             ;
    }
   
//cout<<"A2 Ok"<<endl ;
//cin >> attente ;

if  (abs(mu-1)<=nu && abs(m-1)<=n) 
    {
    x1 = pow ( (n+m)*(n-m+1.0 )*(nu+mu)*(nu-mu+1.0 ),0.5 ) ;
    i_nu = nu*nu+nu-(mu-1) ;
    i_n  = n*n+n-(m-1) ;
    Aout = Aout +  x1 * (*stm) (i_n,i_nu) ;
    }
//cout<<"A3 Ok"<<endl ;
//cin >> attente ;

x1 = 0.5  * pow ( 1.0 /nu/(nu+1.0 )/n/(n+1.0 ),0.5 ) ;
Aout = Aout * x1 ;

//cout<<"A4 Ok"<<endl ;
//cin >> attente ;

// STEP 2 : Evaluation of Bmnnumu coefficients from (*stm)  matrix
// ==============================================================

if   (abs(mu)<=(nu-1) ) 
    { 
    i_nu = (nu-1)*(nu-1)+(nu-1)-mu ;
    i_n  = n*n+n-m ;
    x1 = pow(double(nu-mu)*double(nu+mu),0.5) ;
    Bout = Bout + 2.0  *  m * x1 * (*stm) (i_n,i_nu) ;
    }
//cout<<"B1 Ok"<<endl ;
//cin >> attente ;

if  (abs(mu+1)<=(nu-1) && abs(m+1)<=n) 
    {
    x1 = pow ( (n-m)*(n+m+1.0 )*(nu-mu)*(nu-mu-1.0 ),0.5 ) ;
    i_nu = (nu-1)*(nu-1)+(nu-1)-(mu+1) ;
    i_n = n*n+n-(m+1) ;
    Bout = Bout +  x1 * (*stm) (i_n,i_nu) ;
    }
//cout<<"B2 Ok"<<endl ;
//cin >> attente ;

if  (abs(mu-1)<=(nu-1) && abs(m-1)<=n) 
    {
    x1 = pow ( (n+m)*(n-m+1.0 )*(nu+mu)*(nu+mu-1.0 ),0.5 ) ;
    i_nu = (nu-1)*(nu-1)+(nu-1)-(mu-1) ;
    i_n = n*n+n-(m-1) ;
    Bout = Bout -  x1 * (*stm) (i_n,i_nu) ;
}
//cout<<"B3 Ok"<<endl ;
//cin >> attente ;

x1 = -0.5  * pow ( (2.0 *nu+1)/(2.0 *nu-1)/nu/(nu+1.0 )/n/(n+1.0 ),0.5 ) ;

Bout = -1.0*Bout * x1 * ci ;
//cout<<"B4 Ok"<<endl ;
//cin >> attente ;

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

	void math1::VectorialTranslationalMatrix::e_HMatrix 
			(int i, int j, cdouble z, double t, double p, 
			TranslationTheoremAlgorithm tip)
// =============================================================================
{
	// Etape 1: initialisation de la Matrice H
	// =======================================
	if  (i != nmax || j !=numax)	{
		nmax   = i ;
		numax  = j ;
		dimn   = 2*nmax *(nmax +2) ;
		dimnu  = 2*numax*(numax+2) ;
		vm = cMatrice (dimn,dimnu) ;
	}
	
	kd0     = z ;
	theta0  = t ;
	phi0    = p ;
	
	// Etape 2: Calcul de la Matrice de translation scalaire
	// =====================================================
	delete stm ;
	stm = new ScalarTranslationalMatrix ;
	stm->s_AttributeTo(nmax,numax,kd0 ,theta0,phi0) ;
	stm->e_AlphaMatrix (tip)	;
	
	// Etape 3: Calcul de la Matrice de translation Vectorielle
	// ========================================================
 	c_HMatrixMackowskiRecursif () ;
	
	// Etape 4: purge de la matrice de translation scalaire
	// ====================================================
	delete stm ;
	stm = new ScalarTranslationalMatrix ;
	

}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::VectorialTranslationalMatrix::g_HMatrix 
        (cMatrice&mat1, int i, int j, cdouble z, 
		double t, double p, TranslationTheoremAlgorithm tip)
// =============================================================================
{

	e_HMatrix(i, j, z, t, p, tip)	;
	mat1=vm ;
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::VectorialTranslationalMatrix::c_HMatrixMackowskiRecursif()
// =============================================================================
{
int i_n,i_nu ;
	   
// Etape 2: Generation de la Matrice Jij
// =====================================
for (int n=1;n<=nmax;n++)
for (int m=n;m>=-n;m--)
for (int nu=1;nu<=numax;nu++)
for (int mu=nu;mu>=-nu;mu--)
    {
	i_n  = n *n +n -m  ;
	i_nu = nu*nu+nu-mu ;
	c_ABMackowskiWithScalarMatrix (n,m,nu,mu) ;
	vm (i_n,i_nu)   			    = Aout ;
	vm (i_n,i_nu+dimnu/2)        = Bout ;
	vm (i_n+dimn/2,i_nu)         = Bout ;
	vm (i_n+dimn/2,i_nu+dimnu/2) = Aout ;
    }
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

	ostream& math1::operator <<(ostream& stream,VectorialTranslationalMatrix o )
// =============================================================================
{
	stream.precision(9);
	stream << showpoint; 
	stream << setiosflags (ios::scientific);
	
	stream<<endl;
	stream <<"Vectorial Translational Matrix"<<endl ;
	stream <<"-----------------------------"<<endl ;
	stream <<"nmax    : "<<setw(5)<<o.nmax <<" "<<setw(5)<<o.dimn <<" "<<endl ;
	stream <<"nmax    : "<<setw(5)<<o.numax<<" "<<setw(5)<<o.dimnu<<" "<<endl ;
	
	stream <<"kd     : "<<setw(19)<<real(o.kd0 )<<" "<<setw(19)<<imag(o.kd0 )<<endl;
	stream <<"Theta  : "<<o.theta0<<endl;
	stream <<"Phi    : "<<o.phi0  <<endl;
	stream <<"-----------------------------"<<endl ;
	
	return stream ;
	
}
	
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::testVectorialTranslationalMatrix ()
// =============================================================================
{

   	double pi=4.0*atan(1.0) ;
	double p,t ;
	cdouble z ;
	VectorialTranslationalMatrix Jij ;
	cMatrice MatJ ;
	int nmax ;
	TranslationTheoremAlgorithm mode1 ;

	cout<<"	Programme DENG1 : TestVectorialTranslationalMatrix "<<endl ;
	cout<<" ==================================================="<<endl ;
	cout<<" "<<endl ;
	cout<<" Real(z) "<<endl ;
//	cin >> p ;
	p = 0.05 ;
	z = cdouble (p,0.0) ;
	cout<<" Theta "<<endl ;
//	cin >> t ;
	t = 30.0/180*pi   ;
	cout<<" Phi "<<endl ;
	p = 130.0/180*pi   ;
//	cin >> p ;
	cout<<" nmax "<<endl ;
	cin >> nmax ;
    
	cout<<" z = "<<z<<endl ;
	cout<<" t = "<<t<<endl ;
	cout<<" p = "<<p<<endl ;

	//	mode1 = chewRecursif ;
	mode1 = brian3Y ;
	
//	z = cdouble(1.0,0.0) ;
	Jij.e_JMatrix (nmax, nmax, z,t,p, mode1) ;
	cout<<Jij<<endl;
	int shape = Jij.dimn;
	cout<<"dimn is " <<shape<<endl;
//	for (int i = 1; i <= shape; i++) {
//		for (int j = 1; j <= shape; j++) {
//
//		}
//	}
//

//		hij[findice(2,1)].g_PointerToMatrix() ;
//	z = cdouble(1.0,0.0) ;
//	Jij.e_HMatrix (nmax, nmax, z,t,p, mode1) ;
//	cout<<Jij<<endl ;

//    Jij.g_JMatrix (n,n,z,t,p,1) ;
	
	
	
/*
	cMatrice matCoefA(1,1), matCoefB(1,1) ;
	VectorialTranslationalMatrix vectT          ;
	vectT.g_RgARgBMatrix (matCoefA,matCoefB,nmax,nmax,z,t,p, mode1) ;

	cout<<"COEFA"<<endl ;
	cout<<matCoefA<<endl ;
	cout<<"COEFB"<<endl ;
	cout<<matCoefB<<endl ;
	*/

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=


