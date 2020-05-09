/*
 *  BesselSpherical.cpp
 *  Voltaire
 *
 *  Created by Jean-Claude Auger on 2/12/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

// ANSI STL C++ headers
// =============================================================================
# include <complex>
# include <math.h>
# include <iostream>
# include <iomanip>
# include <fstream>

// Project hearders
// =============================================================================
#include "BesselSpherical.h"

// Using namspace by default
// =============================================================================

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::BesselSpherical::BesselSpherical()
// =============================================================================
{
	nmax  = 1 ;
	nbdim = 1 ;
	bessf = cTableau(0,0,0,0) ;
	kr    = cdouble (0.0, 0.0) ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::BesselSpherical::
   BesselSpherical (BesselSpherical const & o)
// =============================================================================
{
	nmax  = o.nmax  ;
	nbdim = o.nbdim ;
	kr    = o.kr    ;
	bessf = o.bessf ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::BesselSpherical& math1::
   BesselSpherical::operator= (BesselSpherical const& o)
// =============================================================================
{
	
	if (this != &o)	{

		nmax  = o.nmax  ;
		nbdim = o.nbdim ;
		kr    = o.kr    ;
		bessf = o.bessf ;
	}
	
	return *this ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::BesselSpherical:: ~BesselSpherical ()
// =============================================================================
{

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::BesselSpherical::e_Jn (int n, cdouble z)
// ==============================================================================
{
	if (n<3)
		n = 3 ;
	
	kr = z ;
	nmax  = n+1 ;
	nbdim = 1 ;
	bessf   = cTableau(1, 1, 0, nmax) ;
	
	c_Jn () ;	
	
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::BesselSpherical::e_Hn (int n, cdouble z)
// =============================================================================
{
	if (n<3)
		n = 3 ;
	kr = z ;
	nmax  = n+1 ;
	nbdim = 4 ;
	
		bessf = cTableau(1, nbdim, 0,nmax)  ;
	
	c_Jn () ;
	c_Yn () ;
	c_Hn () ;
	
	nmax = nmax -1 ;
	
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::BesselSpherical::
   e_AllBesselSpherical1 (int n, cdouble z)
// ===========================================================================
{
	if (n<3)
		n = 3 ;
	kr = z ;
	nmax  = n+1 ;
	nbdim = 8 ;
	bessf   = cTableau(1, nbdim, 0, nmax) ; 
	
	c_Jn () ;
	c_Yn () ;
	c_Hn () ;
	c_DerivativeFunction () ;	

//	nmax = nmax -1 ;

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::BesselSpherical::
   e_AllBesselSpherical2 (int n, cdouble z)
// =========================================================================
{
	
	e_AllBesselSpherical1 (n, z) ;
	
	for (int i=0; i<nmax; i++)	{
		bessf(5,i) = bessf(1,i) + kr * bessf(5,i) ;
		bessf(6,i) = bessf(2,i) + kr * bessf(6,i) ;
		bessf(7,i) = bessf(3,i) + kr * bessf(7,i) ;
		bessf(8,i) = bessf(4,i) + kr * bessf(8,i) ;
		
		bessf(1,i) = kr * bessf(1,i) ;
		bessf(2,i) = kr * bessf(2,i) ;
		bessf(3,i) = kr * bessf(3,i) ;
		bessf(4,i) = kr * bessf(4,i) ;
	}

//	nmax = nmax -1 ;

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::BesselSpherical::c_Jn ()
// =============================================================================
{
//	cout<<"c_Jn IN "<<endl ;
	
	double a0 ;
	int nm, m ;
	cdouble csa, csb, cf0, cf1, cf, cs ;
	
	a0 = abs(kr) ;
	nm = nmax ;
	
//	cout<<a0<<endl  ;
	
	if (a0<1.0e-60)	{
	//	cout<<"Passage 1 "<<endl ;

		bessf(1,0)   = cdouble (1.0, 0.0) ;
		for (int i=1;i<=nmax;i++)
			bessf(1,i) = cdouble (0.0, 0.0) ;
	}
	else	{
//		cout<<"Passage 2 "<<endl ;
		
		// Etape 1: calcul de J0 et J1
		// ===========================
		bessf(1,0) = sin(kr)/kr ;
		bessf(1,1) = (bessf(1,0) - cos(kr))/kr ;
		csa = bessf(1,0) ;
		csb = bessf(1,1) ;
		
		// Etape 2: calcul de l'indice de depart pour la recurrence
		// ========================================================
		m = startingPointBackwardRecurrence1 (a0, 200) ;
//		cout<<"m1 = : "<<m<<endl ;
		if (m<nmax)
			nm = m ;
//		else
//			m = startingPointBackwardRecurrence2 (a0,nmax, 15) ;
		
//		cout<<"m2 = : "<<m<<endl ;
		
		// Etape 3: formule de r√©currence
		// ==============================
		cf0 = cdouble (0.0,0.0) ;
		cf1 = cdouble (1.0e-100,0.0) ;
		for (int k=m; k>=0; k--)	{ 
			cf = double(2.0*k+3.0) * cf1/kr-cf0 ;
			if (k<=nm)
				bessf(1,k) = cf ;
			cf0 = cf1 ;
			cf1 = cf  ;
		}
		
		if ( abs(csa) >  abs(csb) )
			cs = csa/cf  ;
		if ( abs(csa) <= abs(csb) )
			cs = csb/cf0 ; 
		
		for (int k=0;k<=nm;k++)
			bessf (1,k) = cs * bessf (1,k) ;
	}
	
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::BesselSpherical::c_Yn ()
// =============================================================================
{
	bessf(2,0) = -cos(kr)/kr ;
	bessf(2,1)=-cos(kr)/kr/kr-sin(kr)/kr;
	for (int i=2; i<=nmax; i++) {
		bessf(2,i)=double(2.0*(i-1.0)+1.0)/kr*bessf(2,i-1)-bessf(2,i-2);
	}
	
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::BesselSpherical::c_Hn ()
// =============================================================================
{
	cdouble ci(0.0,1.0) ;
	for (int i=0; i<=nmax; i++)	{
		bessf(3,i) = bessf(1,i) + ci* bessf(2,i) ;
		bessf(4,i) = bessf(1,i) - ci* bessf(2,i) ;
	}
	
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::BesselSpherical::c_DerivativeFunction ()
// =============================================================================
{
	double ii ;
	
	cdouble cii (0.0,1.0) ;
	
	bessf(5,0)   =  (cos(kr)*kr-sin(kr))/kr/kr;
	bessf(6,0)   =  (sin(kr)*kr+cos(kr))/kr/kr;
	bessf(7,0) = bessf(5,0)+ cii*bessf(6,0);
	bessf(8,0) = bessf(5,0)- cii*bessf(6,0);
	
	for (int i=1; i<nmax; i++)	{
		ii = double(i) ;
		bessf(5,i)   = (1.0/(2.0*ii+1.0)) * 
		(ii*bessf(1,i-1)-(ii+1.0)*bessf(1,i+1)) ;
		bessf(6,i)   = (1.0/(2.0*ii+1.0)) * 
		(ii*bessf(2,i-1)-(ii+1.0)*bessf(2,i+1)) ;
		bessf(7,i)   = (1.0/(2.0*ii+1.0)) * 
		(ii*bessf(3,i-1)-(ii+1.0)*bessf(3,i+1)) ;
		bessf(8,i)   = (1.0/(2.0*ii+1.0)) * 
		(ii*bessf(4,i-1)-(ii+1.0)*bessf(4,i+1)) ;   
	}
	
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   double math1::BesselSpherical:: envj(int n, double x)
// =============================================================================
{
	double envjr ;
	envjr = 0.5*log(6.28*n)-n*log(1.36*x/n) ; 
	return envjr ;
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   int math1::BesselSpherical::
   startingPointBackwardRecurrence1(double x, int mp)
// =============================================================================
{
	int ms ;
	int n0, n1, it,nn = 0 ;
	double a0, f, f0, f1 ;
	
	//cout<<" startingPointBackwardRecurrence1 IN "<<endl ;
	
	a0 = fabs(x) ;
	n0 = int (1.1*a0) + 1 ;
	f0 = envj (n0, a0) - mp ;
	n1 = n0 + 5 ;
	f1 = envj (n1, a0) - mp ;
	
	for (it=1;it<=20;it++)	{
		nn = int((n1 - (n1-n0)/(1.0-f0/f1))) ;
		f  = envj (nn, a0) - mp ;
		if (abs(nn-n1) <1)
			break ; 
		n0 = n1 ;
		f0 = f1 ;
		n1 = nn ;
		f1 = f  ;
	}
	ms = nn ;
	//cout<<" startingPointBackwardRecurrence1 OUT "<<endl ;
	
	return ms ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   int math1::BesselSpherical::
   startingPointBackwardRecurrence2(double x, int n, int mp)
// =============================================================================
{
	int ms ;
	double ejn,a0, hmp, obj, f0, f1, f ;
	int  n0, n1, nn = 0, it ;
	//cout<<" startingPointBackwardRecurrence2 IN "<<endl ;
	
	a0=fabs(x) ;
	hmp = 0.5*mp ;
	ejn = envj (n, a0) ;
	
	if (ejn <= hmp)	{
		obj = mp ;
		n0 = int(1.1*a0) ;
	}
	else	{
		obj = hmp + ejn ;
		n0 = n ;
	}
	
	f0 = envj (n0, a0) - obj ;
	n1 = n0 + 5 ;
	f1 = envj (n1, a0) - obj ;
	
	for (it=1;it<=20;it++)	{
		nn = int((n1 - (n1-n0)/(1.0-f0/f1))) ;
		f  = envj (nn, a0) - obj ;
		if (abs(nn-n1) <1)
			break ; 
		n0 = n1 ;
		f0 = f1 ;
		n1 = nn ;
		f1 = f  ;
	}
	ms = nn + 10 ;
	
	return ms ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   ostream& math1::operator <<(ostream& stream, BesselSpherical o )
// =============================================================================
{
// =============================================================================
	int i ;
	stream.precision(9);
	stream.setf(ios::scientific) ;
	stream.setf(ios::showpoint) ;
// =============================================================================
	
    // =========================================================================
    
        stream<<endl ;
        stream<<"Bessel Functions"<<endl ;
        stream<<"----------------"<<endl ;
        stream<<"nmax   :"<<setw(5)<<o.nmax<<endl;
        stream<<"bndim  :"<<setw(5)<<o.nbdim<<endl;
        stream<<"kr     :"<<setw(19)<<real(o.kr)<<setw(19)<<imag(o.kr)<<endl ;
        stream<<"----------------"<<endl ;
        
        stream
        <<setw(5)<<"No"
        <<setw(19)<<"re(Jn)" <<setw(19)<<"im(Jn)"
        <<setw(19)<<"re(Yn)" <<setw(19)<<"im(Yn)"
        <<setw(19)<<"re(Hn1)"<<setw(19)<<"im(Hn1)"
        <<setw(19)<<"re(Hn2)"<<setw(19)<<"im(Hn2)"
        <<endl ;
        
        
        for (i=0;i<=o.nmax;i++){
            stream
            <<setw(5)<<i
            <<setw(19)<<real(o.bessf(1,i))<<setw(19)<<imag(o.bessf(1,i)) ;
            
            if (o.nbdim>1) {
                stream
                <<setw(19)<<real(o.bessf(2,i))<<setw(19)<<imag(o.bessf(2,i))
                <<setw(19)<<real(o.bessf(3,i))<<setw(19)<<imag(o.bessf(3,i))
                <<setw(19)<<real(o.bessf(4,i))<<setw(19)<<imag(o.bessf(4,i))
                <<endl ;
            }
            else {
                stream<<endl ;
            }
        }
        
        
        
        if (o.nbdim>4) {
            stream
            <<endl<<endl
            <<setw(5)<<"No"
            <<setw(19)<<"re(dJn)" <<setw(19)<<"im(dJn)"
            <<setw(19)<<"re(dYn)" <<setw(19)<<"im(dYn)"
            <<setw(19)<<"re(dHn1)"<<setw(19)<<"im(dHn1)"
            <<setw(19)<<"re(dHn2)"<<setw(19)<<"im(dHn2)"
            <<endl ;
            
            
            for (i=0;i<=o.nmax;i++){
                stream
                <<setw(5)<<i
                <<setw(19)<<real(o.bessf(5,i))<<setw(19)<<imag(o.bessf(5,i)) 				
                <<setw(19)<<real(o.bessf(6,i))<<setw(19)<<imag(o.bessf(6,i)) 
                <<setw(19)<<real(o.bessf(7,i))<<setw(19)<<imag(o.bessf(7,i)) 
                <<setw(19)<<real(o.bessf(8,i))<<setw(19)<<imag(o.bessf(8,i))
                <<endl ;
            }
        }
        

        

     
	
	return stream ;   
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=


   void math1::testBesselSpherical ()
// =============================================================================
{
// =============================================================================
	int n ;
	cdouble kz ;
    BesselSpherical bess_function ;
	BesselSpherical bs1 ;
	ofstream out1 ;
// =============================================================================


	cout.precision(9);
	cout.setf(ios::scientific) ;
	cout.setf(ios::showpoint) ;
		
	n = 3 ;
	kz = cdouble(1.50, 0.0) ;
	bess_function.e_AllBesselSpherical2(n,kz) ;
	cout<<bess_function<<endl ;
	
	
	/*
	bess_function.e_AllBesselSpherical2(n,kz) ;
	
	for (int i=0; i<=n; i++){
		cout
		<<setw(5)<<i
		<<setw(19)<<real(bess_function(5,i)/bess_function(1,i))
		<<setw(19)<<imag(bess_function(5,i)/bess_function(1,i))
		<<setw(19)<<real(bess_function(7,i)/bess_function(3,i))
		<<setw(19)<<imag(bess_function(7,i)/bess_function(3,i))
		<<endl ;
	
	}
	 */
	
	/*
	cout<<"Program iTECHS : Test class BesselSpherical"<<endl ;
	cout<<"==========================================="<<endl ;
	cout<<" "<<endl ;
	
	choix1 = 0 ;
	while (choix1==0)
	{
		cout<<" 1  - Calcul Jn et Hn "<<endl ;
		cout<<" 2  - Calcul AllBessel1"<<endl ;
		cout<<" 3  - Calcul AllBessel2"<<endl ;
		cout<<" 10 - Out "<<endl;
		cout<<" "<<endl ;
		cin >>choix2 ;
		switch (choix2)	
		{
			case 1:
				cout<<" nmax"<<endl;
				cin >>  n ;
				cout<<" Re(Arg), Im(Arg)"<<endl;
				cin >>  r1 ;
				cin >>  r2 ;
				kz = cdouble(r1,r2) ;
				
				bess_function.e_Jn(n,kz) ;
				cout <<bess_function ;
				break ;
				
			case 2:
				out1.open("BesselSpherical1.txt") ;
				cout<<" nmax"<<endl;
				cin >>  n ;
				cout<<" Re(Arg), Im(Arg)"<<endl;
				cin >>  r1 ;
				cin >>  r2 ;
				kz = cdouble(r1,r2) ;
				bess_function.e_AllBesselSpherical1(n,kz) ;
				cout <<bess_function ;
				out1 <<bess_function ;
				cout<<"----------"<<endl ;
				out1.close() ;
				break ;
				
			case 3:
				out1.open("BesselSpherical2.txt") ;
				cout<<" nmax"<<endl;
				cin >>  n ;
				cout<<" Re(Arg), Im(Arg)"<<endl;
				cin >>  r1 ;
				cin >>  r2 ;
				kz = cdouble(r1,r2) ;
				bess_function.e_AllBesselSpherical2(n,kz) ;
				cout <<bess_function ;
				out1 <<bess_function ;
				cout<<"----------"<<endl ;
				out1.close() ;
				break ;
												
			case 10:
				choix1 = 1 ;
				break ;
				
		}
	}
	 */
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

