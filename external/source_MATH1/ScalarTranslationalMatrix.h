/*
 *  scalarTranslationalMatrix.h
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

// Class ScalarTranslationalMatrix
// =============================================================================
# ifndef ScalarTranslationalMatrix_H
# define ScalarTranslationalMatrix_H

// Project classes
// =============================================================================
#include "Math1.h"
#include "TableauX.h"
#include "Tableau.h"
#include "Matrice.h"

// Name space
// =============================================================================
using namespace std ;
using namespace math1 ;

// Class definition
// =============================================================================
class math1::ScalarTranslationalMatrix{

private:
	// user input variables 
	// ==========================================================================
	int nmax, numax ;
	int dimn,dimnu  ;
	double theta0, phi0 ;
    cdouble kd0 ;
	
	// user output variables 
	// ==========================================================================
	cTableau sm ;
	double ffac[dimFactorielMax+1] ;

public:
	// Coplien canonical class
	// ==========================================================================
	ScalarTranslationalMatrix () ;
	ScalarTranslationalMatrix (int, int, cdouble, double, double) ;
	ScalarTranslationalMatrix (const ScalarTranslationalMatrix&) ;
	ScalarTranslationalMatrix& operator=(const ScalarTranslationalMatrix&) ;
	~ScalarTranslationalMatrix () ;

	// operator overloading
	// ==========================================================================
	cdouble& operator ()  (int i,int j)	{ 
		return sm(i,j) ; 
	}
	
	// User input function
	// ==========================================================================
	void s_AttributeTo (int, int, cdouble, double, double) ;
	void e_BetaMatrix  (TranslationTheoremAlgorithm)         ;
	void e_AlphaMatrix (TranslationTheoremAlgorithm)         ;
	
	// User output function
	// ==========================================================================
	
	// Friend functions 
	// ==========================================================================
	friend ostream & operator << (ostream&,ScalarTranslationalMatrix ) ;

private:
	// Internal functions
	// ==========================================================================
	inline double aplus  (int, int) ;
	inline double amoins (int, int) ;
	inline double bplus  (int, int) ;
	inline double bmoins (int, int) ;
	void c_Ynm    (int, double, double, Matrice<cdouble > &) ;

	void c_BetaMatrixChewRecursif          () ;
	void c_BetaMatrixBrian3Y               () ;

	void c_AlphaMatrixChewRecursif         () ;
	void c_AlphaMatrixBrian3Y              () ;

	double c_3Y0BrianAvecFactoriel (int, int, int, int)            ;
	void   c_3Y0BrianRecurrence    (TableauX<double> &)             ;
	void   c_3YBrian (int, int, int, int, int, TableauX<double> &)  ;

} ;
#endif 
