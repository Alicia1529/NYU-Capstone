/*
 *  vectorialTranslationalMatrix.h
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

// ANSI MSL C++ headers
// =============================================================================

// Class VectorialTranslationalMatrix
// =============================================================================
# ifndef VectorialTranslationalMatrix_H
# define VectorialTranslationalMatrix_H

// Project classes
// =============================================================================
#include "Math1.h"
#include "Matrice.h"
#include "TableauX.h"
#include "ScalarTranslationalMatrix.h"

// Name space
// =============================================================================
using namespace std ;


// Class definition
// =============================================================================
class math1::VectorialTranslationalMatrix{

public:
	// user input variables 
	// ==========================================================================
	int nmax, numax ;
	long int dimn,dimnu ;
	cdouble kd0 ;
	double theta0, phi0 ;

	// user output variables 
	// ==========================================================================
	cMatrice  vm  ;
	ScalarTranslationalMatrix  *stm ;
	cdouble Aout,Bout       ;


	// Coplien canonical class
	// ==========================================================================
	VectorialTranslationalMatrix () ;
	~VectorialTranslationalMatrix () ;
	VectorialTranslationalMatrix (int, int, cdouble, double, double) ;
	VectorialTranslationalMatrix (const VectorialTranslationalMatrix&) ;
	VectorialTranslationalMatrix& operator= (const VectorialTranslationalMatrix&) ;
 

 	// operator overloading
	// ==========================================================================
	inline cdouble& operator () (int i, int j) { 
		if (i>=1 && i<=dimn && j>=1 && j<=dimnu)	{
			return vm(i,j) ;
		}
		else	{
			cout<<"classe   : VectorialTranslationalMatrix "<<endl ;
			cout<<"Fonction : Operator (i,j)                           "<<endl ;
			cout<<"Erreur1  : Indice incompatible avec les dimensions"<<endl ;
			cout<<" i "<<i<<"   dimn  = "<<dimn <<endl ;
			cout<<" j "<<j<<"   dimnu = "<<dimnu<<endl ;
			return vm(1,1) ;
		}
	}
	

	
	// User input function
	// ==========================================================================
	
	// User output function
	// ==========================================================================
	void e_JMatrix (int, int, cdouble, double, double,
								 TranslationTheoremAlgorithm) ;
	
	void e_HMatrix (int, int, cdouble, double, double,
								 TranslationTheoremAlgorithm) ;

	void g_JMatrix (cMatrice&,int, int,
				 cdouble, double, double, TranslationTheoremAlgorithm);
				 
	void g_HMatrix (cMatrice&,int, int,
				 cdouble, double, double, TranslationTheoremAlgorithm);


	void g_RgARgBMatrix (cMatrice&,cMatrice&,
					  int, int, cdouble, double, double,
					  TranslationTheoremAlgorithm) ;
					  
	void g_ABMatrix (cMatrice&,cMatrice&,
				  int, int, cdouble, double, double,
				  TranslationTheoremAlgorithm) ;
	
	cMatrice& g_PointerToMatrix ()	{return vm ;}

	// Friend functions 
	// ==========================================================================
	friend ostream& operator <<(ostream& stream,VectorialTranslationalMatrix) ;


private:
	// Internal functions
	// ==========================================================================
	void c_HMatrixMackowskiRecursif () ;
	void c_JMatrixMackowskiRecursif () ;
	void c_ABMackowskiWithScalarMatrix (int&,int&,int&,int&) ;

} ;
#endif 
