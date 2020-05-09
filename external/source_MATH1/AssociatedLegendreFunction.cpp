/*
 *  AssociatedLegendreFunction.cpp
 *  Voltaire
 *
 *  Created by Jean-Claude Auger on 1/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
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
#include "AssociatedLegendreFunction.h"

// Using namspace by default
// =============================================================================
using namespace math1 ;

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::AssociatedLegendreFunction::AssociatedLegendreFunction ()

// =============================================================================
{
	eps = 1.0e-9 ;
	nmax   = 0   ; 
	theta  = 0.0 ;
	ctheta = cos(theta)   ;
	type_of_calculation = none ;
	px = dTableau(0,0)    ;
}  
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::AssociatedLegendreFunction
                  ::AssociatedLegendreFunction (int n, double x)

// =============================================================================
{
	eps = 1.0e-9 ;
	nmax   = n                   ;
	theta  = x                   ;
	ctheta = cos(theta)          ;
	type_of_calculation = all    ;
//	px = dTableau(1,3,0,nmax*(nmax+2))     ;
	px = dTableau(0,0)     ;

}  
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::AssociatedLegendreFunction
   ::AssociatedLegendreFunction (AssociatedLegendreFunction const& o)

// =============================================================================
{
	eps    = o.eps    ;
	nmax   = o.nmax   ;
	theta  = o.theta  ;
	ctheta = o.ctheta ;
	px     = o.px     ;
	type_of_calculation = o.type_of_calculation ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::AssociatedLegendreFunction& math1::
   AssociatedLegendreFunction::operator = (const AssociatedLegendreFunction &o)
// =============================================================================
{
	if (this != &o)	{
		
		eps    = o.eps    ;
		nmax   = o.nmax   ;
		theta  = o.theta  ;
		ctheta = o.ctheta ;
		px     = o.px     ;
		type_of_calculation = o.type_of_calculation ;
	}
	
	return *this ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   math1::AssociatedLegendreFunction::~AssociatedLegendreFunction()
// =============================================================================
{
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::AssociatedLegendreFunction::e_Pnm(int n, double x)
// =============================================================================
{
	nmax = n                   ;
	theta  = x                 ;
	ctheta = cos(theta)        ;	
	
	type_of_calculation = onlyPnm ;
	px = dTableau(1,1,0,nmax*(nmax+2)) ;	
	c_ALF1 () ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::AssociatedLegendreFunction::e_AllFunctions (int n, double x)
// =============================================================================
{
	nmax = n                   ;
	theta  = x                 ;
	ctheta = cos(theta)        ;	
	
	type_of_calculation = all ;
	px = dTableau(1,3,0,nmax*(nmax+2)) ;		
	c_All () ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::AssociatedLegendreFunction::c_All ()
// =============================================================================
{
	c_ALF1 () ;
	c_ALF2 () ;
	c_ALF3 () ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::AssociatedLegendreFunction::c_ALF1 ()
// =============================================================================
{
	int angle ;
	
	// Test if theta=0 or theta=Pi
	// ===========================
	angle=0;
	if ( fabs(ctheta-1.0)<=eps && ctheta>0)
		angle=1;												// cos(theta)=1 and theta=0
	if ( fabs(fabs(ctheta)-1.0)<=eps && ctheta<0)
		angle=2;												// cos(theta)=-1 and theta=Pi
	
	//cout<<"calculateALF1 angle = "<<angle<<endl ;
	
	// Calculation of P00
	// ==================
	px(1,0)=1.0;
	
	// Calculation of the Pnm such that n=1 to n=nmax
	// ==============================================
	int n,m;
	switch (angle)	{
			// Theta different from 0 and Pi
			// =============================
		case 0:
			// Evaluation of P11, P10 and P1-1
			// ===============================
			px(1,1)=-sin(theta);
			px(1,2)=ctheta;
			px(1,3)=-0.5*px(1,1);
			
			for (n=2; n<=nmax; n++)	{
				// Evaluation of Pn,n and Pn+1,n
				// =============================
				m=n;
				px(1,n*n)=mun(n)*ffa(2*n-1)*pow((1-ctheta*ctheta),double(n)/2.0);
				px(1,n*n+n+m)=mun(m)*fa(n-m)/fa(n+m)*px(1,n*n);
				
				m=n-1;
				px(1,n*n+n-m)= ctheta*(2*n-1)*px(1,(n-1)*(n-1));
				px(1,n*n+n+m)=mun(m)*fa(n-m)/fa(n+m)*px[n*n+n-m];	
				
				// Evaluation of Pn,n-i, i=2 to n
				// ==============================
				for (m=n-2;m>=0;m--)	{
					px[n*n+n-m]=1.0/(n-m)*( ctheta*(2*n-1)*px[(n-1)*(n-1)+(n-1)-m] 
										   -(n+m-1)*px[(n-2)*(n-2)+(n-2)-m]);
					if (m!=0)
						px[n*n+n+m]=mun(m)*fa(n-m)/fa(n+m)*px[n*n+n-m];
				}
			}
			break;
			
			// Theta = 0
			// =========
		case 1:
			for (n=1;n<=nmax;n++)	{
				for (m=n;m>=0;m--)	{
					if (m==0)   {
						px[n*n+n-m]=1.0;
					}
					else   {
						px[n*n+n-m]=0.0;
						px[n*n+n+m]=0.0;
					}
				}
			}
			break;
			
			// Theta= Pi
			// =========
		case 2:
			for (n=1;n<=nmax;n++)	{
				for (m=n;m>=0;m--)	{	   
					if (m==0)   {
						px[n*n+n-m]=mun(n);
					}
					else   {
						px[n*n+n-m]=0.0;
						px[n*n+n+m]=0.0;
					}   	
				}
			}
			break;
	}
	
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::AssociatedLegendreFunction::c_ALF2 ()
// =============================================================================
{
	int angle ;
	// Test if theta=0 or theta=Pi
	// ===========================
	angle=0;
	if ( fabs(ctheta-1.0)<=eps && ctheta>0)
		angle=1;								   // cos(theta)=1 and theta=0
	if ( fabs(fabs(ctheta)-1.0)<=eps && ctheta<0)
		angle=2;								   // cos(theta)=-1 and theta=Pi
	
	//cout<<"calculateALF2 angle = "<<angle<<endl ;
	
	int n, m ;
	// Calculation of Pi00
	// ===================
	px(2,0) = 0.0;
	
	switch (angle)	{
		case 0:
			// Theta different from 0 and Pi
			// =============================
			for (n=1; n<=nmax; n++)
				for (m=n; m>=-n; m--)
					px(2,n*n+n-m)=double(m)/sin(theta)*px(1,n*n+n-m) ;	
			break;
			
		case 1:
			// Theta = 0
			// =========
			for (n=1;n<=nmax;n++)
				for (m=n;m>=-n;m--)	{
					if (m==1)
						px(2,n*n+n-m)= 0.5*n*(n+1.0)*mun(m) ;
					if (m==-1)
						px(2,n*n+n-m)=-0.5*m*mun(m) ;
				}
			break;
			
		case 2:
			// Theta = Pi
			// ==========
			for (n=1;n<=nmax;n++)
				for (m=n;m>=-n;m--)	{
					if (m==1)
						px(2,n*n+n-m)=0.5*n*(n+1.0)*mun(m)*mun(n+1) ;
					if (m==-1)
						px(2,n*n+n-m)=0.5*mun(n)*m*mun(m) ;
				}
			break;
	}
	
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::AssociatedLegendreFunction::c_ALF3 ()
// =============================================================================
{
	int angle ;	
	// Test if theta=0 or theta=Pi
	// ===========================
	angle=0;
	if ( fabs(ctheta-1.0)<=eps && ctheta>0)
		angle=1 ;								   // cos(theta)=1 and theta=0
	if ( fabs(fabs(ctheta)-1.0)<=eps && ctheta<0)
		angle=2 ;								   // cos(theta)=-1 and theta=Pi
																
	
	// Calculation of Tau00
	// ====================
	px(3,0) = 0.0 ;
	
	//cout<<"calculateALF3 angle = "<<angle<<endl ;
	
	int n,m ;
	switch (angle)	{
		case 0:
			// Theta different from 0 and Pi
			// =============================
			for (n=1;n<=nmax;n++)
				for (m=n;m>=-n;m--)	{
					px(3,n*n+n-m)=ctheta*px(2,n*n+n-m) ;
					if (m+1<=n)
						px(3,n*n+n-m) =px(3,n*n+n-m) +px(1,n*n+n-(m+1));
				}
			break;
			
		case 1:
			// Theta = 0
			// =========
			for (n=1;n<=nmax;n++)
				for (m=n;m>=-n;m--)	{
					if (m==1)
						px(3,n*n+n-m)=0.5*n*(n+1.0)*mun(m) ;
					if (m==-1)
						px(3,n*n+n-m)=-0.5*mun(m) ;
				}
			break;
			
		case 2:
			// Theta = Pi
			// ==========
			for (n=1;n<=nmax;n++)
				for (m=n;m>=-n;m--)	{
					//				cout<<"Theta = Pi " <<n<<"   "<<m<<endl ;
					if (m==1)
						px(3,n*n+n-m)=mun(n)*n*(n+1.0)*0.5*mun(m);
					if (m==-1)
						px(3,n*n+n-m)=mun(n+1)*0.5*mun(m); 
					
					//				cout<<px[i3+n*n+n-m]<<endl ;
				}
			break;
	}
	
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   ostream& math1::
   operator <<(ostream& stream, AssociatedLegendreFunction o )
// =============================================================================
{
// =============================================================================
	stream.precision(9);
	stream.setf(ios::scientific) ;
	stream.setf(ios::showpoint) ;
// =============================================================================
	
    // =========================================================================
    
        stream <<endl ;
        stream <<"Associated Legendre Function"   <<endl ;
        stream <<"----------------------------"   <<endl ;
        stream <<"nmax          : "<<o.nmax       <<endl ;
        stream <<"cTheta        : "<<o.ctheta     <<endl ;
        stream <<"----------------------------"   <<endl ;
        
        stream<<setw(5)<<"n"
        <<setw(19)<<"Pnm"
        <<setw(19)<<"Pinm"
        <<setw(19)<<"Taunm"<<endl ;
        
        for (int n=0;n<=o.nmax;n++)
            for (int m=n;m>=-n     ;m--) {
                
                if (o.type_of_calculation==o.all)
                    stream<<setw(5)<<n<<setw(5)<<m
                    <<setw(19)<<o(1,n,m)
                    <<setw(19)<<o(2,n,m)
                    <<setw(19)<<o(3,n,m)<<endl ;
                
                if (o.type_of_calculation==o.onlyPnm)
                    stream<<setw(5)<<n<<setw(5)<<m<<setw(19)<<o(1,n,m)<<endl ;
                
            }

        
    
		
	return stream ;	
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   void math1::testAssociatedLegendreFunction ()
// =============================================================================
{
	
	
	cout<<"Program VOLTAIRE: Test class AssociatedLegendreFunction"<<endl ;
	cout<<"====================================================="<<endl ;
	cout<<endl ;
	
	AssociatedLegendreFunction aleg ;
//	aleg.e_Pnm(3, 0.0) ;
//	cout<<aleg<<endl ;
	
	int n ;
	double x ;

	cout <<" nmax et arg (deg), "<< endl ;
	cin >> n ;
	cin >> x ;
	
	aleg.e_AllFunctions(n, x/180.0*4*atan(1)) ;
	cout<<aleg<<endl ;
	

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=



















