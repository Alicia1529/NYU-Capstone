/*
 *  BesselSpherical.h
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


// Class BesselSpherical
// =============================================================================
# ifndef BesselSpherical_H
# define BesselSpherical_H

// ANSI STL C++ headers
// =============================================================================

// Project hearders
// =============================================================================
#include "Math1.h"
#include "Tableau.h"

// Name space
// =============================================================================
using namespace std       ;
using namespace math1     ;


// Class definitiion
// =============================================================================
class math1::BesselSpherical {

private:
    // user input variables
    // =========================================================================
	int	nmax   ;
	int nbdim  ;
	cdouble kr ;
	
    // user output variables
    // =========================================================================
	cTableau bessf ;
	
	
public:
	// Coplien canonical class
	// =========================================================================
	BesselSpherical () ;
	BesselSpherical (const BesselSpherical &) ;
	BesselSpherical& operator  = (const BesselSpherical &) ;
	~BesselSpherical () ;
	
	// operator overloading
	// =========================================================================
	inline cdouble& operator () (int i, int j) {return bessf(i,j) ;}

	// User input function
	// =========================================================================
	void e_Jn (int, cdouble)                  ;
	void e_Hn (int, cdouble)                  ;
	void e_AllBesselSpherical1 (int, cdouble) ;
	void e_AllBesselSpherical2 (int, cdouble) ;
		
	// User output function
	// =========================================================================
	int     g_nmax ()	{return nmax ;}
	cdouble g_arg  ()	{return kr   ;}
	
	// Manipulation function
	// =========================================================================
	
	// Friend functions 
	// =========================================================================
	friend ostream& operator <<(ostream&, BesselSpherical) ;

private:
	// Internal functions
	// =========================================================================
	void c_Jn () ;
	void c_Yn () ;
	void c_Hn () ;
	void c_DerivativeFunction () ;

	int startingPointBackwardRecurrence1 (double, int)      ;
	int startingPointBackwardRecurrence2 (double, int, int) ;
	double envj (int, double)                                 ;
	
} ;

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

#endif
