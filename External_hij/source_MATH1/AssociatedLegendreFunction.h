/*
 *  AssociatedLegendreFunction.h
 *  Voltaire
 *
 *  Created by Jean-Claude Auger on 1/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */
// =============================================================================


// Class AssociatedLegendreFunction
// =============================================================================
#ifndef AssociatedLegendreFunction_H
#define AssociatedLegendreFunction_H

// ANSI MSL C++ classes
// =============================================================================

// Project classes
// =============================================================================
#include "Math1.h"
#include "Tableau.h"

// Name space
// =============================================================================
using namespace std       ;
using namespace math1     ;


// Class definitiion
// =============================================================================
class math1::AssociatedLegendreFunction {
    
private:
    // user input variables
    // =========================================================================
	int    nmax    ;
	double ctheta  ;
	double theta   ;
	double eps     ;
	
	enum calculationType {
		none,
		onlyPnm,
		all		
	} ;
    calculationType type_of_calculation ;

    // user output variables
    // =========================================================================
    dTableau px    ;
	
		
public:
    // Coplien canonical class
    // =========================================================================
	AssociatedLegendreFunction ();
	AssociatedLegendreFunction (int, double) ;
	AssociatedLegendreFunction             (const AssociatedLegendreFunction &) ;
	AssociatedLegendreFunction& operator = (const AssociatedLegendreFunction &) ;
	~AssociatedLegendreFunction();
	
    // operator overloading
    // =========================================================================
	inline double & operator () (int i, int n, int m) {
		return px(i,n*n+n-m) ;
	}
	
    // User input function
    // =========================================================================
	void e_AllFunctions (int, double) ;
	void e_Pnm          (int, double) ;
	
    // User output function
    // =========================================================================
	int    g_nmax  ()	{return nmax ;}
	double g_theta ()	{return theta ;}
	
	// Friend function
	// ==========================================================================
	friend ostream& operator <<(ostream&,AssociatedLegendreFunction) ;
	
private:
	// Internal Functions
	// ==========================================================================
	void c_All  ()   ;
	void c_ALF1 ()   ;
	void c_ALF2 ()   ;
	void c_ALF3 ()   ;
	
} ;
#endif

