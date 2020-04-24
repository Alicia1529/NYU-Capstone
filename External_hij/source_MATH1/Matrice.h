/*
 *  Matrice.h
 *  Voltaire
 *
 *  Created by Jean-Claude Auger on 1/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

// Class Matrice
// =============================================================================
# ifndef Matrice_H
# define Matrice_H

//using namespace math1 ;


// ANSI STL C++ headers
// =============================================================================
#include <iostream>
#include <complex>
#include <typeinfo>
#include "Math1.h"

// Project hearders
// =============================================================================


// Using namespace
// =============================================================================
using namespace std   ;

// Class definition
// =============================================================================
template <class T> class math1::Matrice
{
	private :
	// Variables 
	// =========
//	Format_of_display display ;
	size_t lig  ;
	size_t col  ;
	size_t dim  ;
	T        *pm  ;
    
public:
	// Coplien canonical class
	// =========================================================================
	Matrice ()                   ;                       
	Matrice (size_t, size_t) ;
	Matrice (const Matrice&)    ;
	~Matrice ()                   ;
	
	// operator overloading
	// =========================================================================
	inline T& operator ()  (size_t i)	{

		if (i<1 || i>dim)	{
			cout<<"Classe      : Matrice                  "<<endl ;
			cout<<"Fonction    : Operator (i)             "<<endl ;
			cout<<"Erreur (1)  : Indice incompatible"<<endl ;
			cout<<i<<" / "<<dim                        <<endl ;
	//		math1::wait() ;
		}
		else	{
			
		return pm[i-1] ;
		}
		
		return pm[0] ;
	}
	// operator overloading
	// =========================================================================
	inline T& operator ()  (size_t i, size_t j)	{
		
		if (i<=0 || i>lig || j<=0 || j>col)	{
            
           /*
            vs1.clear() ;
            vs2.clear() ;
            
            vs1.push_back("CALCULATION ON AXI-SYMMETRIC COMPOUND");
            vs1.push_back(" ") ;
            
            vs2.push_back("NAMESPACE: math1");
            vs2.push_back("CLASS    : Matrice");
            vs2.push_back("FUNCTION : Operator (i,j)");
            vs2.push_back("OBJECT PROPERTIES");
            vs2.push_back(" ") ;
            
            vs1.push_back(" - Indices out of range") ;
            vs1.push_back
            ("given: "+math1::cts((int)i)+" |  max value: "+math1::cts((int)lig));
            vs1.push_back
            ("given: "+math1::cts((int)j)+" |  max value: "+math1::cts((int)col));
            vs1.push_back(" ") ;

            vs1.push_back("<end> ERROR");
            vs1.push_back(" ") ;
            vs2.push_back("<end> ERROR");
            vs2.push_back(" ") ;
            
            throw error::Err_Matrice(vs1, vs2) ;
            */

			cout<<"Classe    : Matrice                  "<<endl ;
			cout<<"Fonction  : Operator (i,j)           "<<endl ;
			cout<<"Erreur (2): Indices incompatibles    "<<endl ;
			cout<<"given i = "<<setw(6)<<i<<" | max lig is: "<<setw(6)<<lig<<endl ;
            cout<<"given j = "<<setw(6)<<j<<" | max lig is: "<<setw(6)<<col<<endl ;
            cout<<endl ;
            return pm[0] ;
		}
		else	{
//			return pm[ (j-1)*lig+i-1 ]  ;  ???
            return pm[ (i-1)*lig+j-1 ]  ;
        }
	}
	// operator overloading
	// =========================================================================	
	Matrice<T>& operator =  (const  Matrice<T>&) ;
	Matrice<T>& operator =  (const T) ;
//	Matrice<T>& operator =  (const Liste<T>&) ;
	
	// User input function
	// =========================================================================
	void resize (size_t, size_t) ; 

	// Algebre lineaire
	// =========================================================================

    

	// User output function
	// =========================================================================
    size_t g_lig () {return lig;}
    size_t g_col () {return col;}
    size_t g_dim () {return dim;}
    T * g_pm() {
        pm  ;
    }



	// Manipulation function
	// =======================================================================
//	void setDisplayTo(Format_of_display o) {display = o;}

	// Friend functions 
	// =========================================================================

 

	
private:
	// Internal functions
	// =========================================================================
	
} ;



// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T>   math1::Matrice<T>::Matrice ()
// =============================================================================
{
	lig   = 1        ;
	col   = 1        ;
	dim   = 1        ;    	
	pm    = new T[1] ;
	pm[0] = 0.0 ;
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T> math1::Matrice<T>::Matrice (size_t a, size_t b)
// =============================================================================
{
	if (a<=0 || b<=0)	{
        cout <<"ERROR: Matrice"<<endl;
		cout <<"Matrice: Indice(s) de la matrice non valables(s)"<<endl;
        cout <<" lig = "<<a<<endl ;
        cout <<" cp; = "<<b<<endl ;
        math1::wait("ERRIR") ;
	}
	else	{
		lig   = a       ;
		col   = b       ;
		dim   = lig*col ;
		pm = new T  [dim] ;
		for (size_t i=1;i<=dim;i++)
			pm[i-1] = 0.0 ;
	}
	
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T> math1::Matrice<T> :: Matrice (const Matrice &o)
// =============================================================================
{

	lig   = o.lig	;
	col   = o.col	;
	dim   = o.dim ;
	pm = new T [dim];
	for (size_t i=0; i<dim; i++)
		pm[i]=o.pm[i];
    
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T> 
   math1::Matrice<T>& math1::Matrice<T>::operator = (const Matrice& o)
// =============================================================================
{
	if (this != &o)	{
		lig   = o.lig  ;
		col   = o.col  ;
		dim   = o.dim  ;	
		delete [] pm   ;

		pm= new T [dim] ;
		for (size_t i=0; i<dim; i++)
			pm[i]=o.pm[i] ;
        
 
	}
	return *this;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

template <class T>
math1::Matrice<T>& math1::Matrice<T>::operator = (const T o)
// =============================================================================
{
		for (int i=1; i<=this->g_dim(); i++)
			(*this)(i) = o ;
	return *this;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T> math1::Matrice<T>:: ~Matrice	() 
// =============================================================================
{
	delete [] pm ;	
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T> void math1::Matrice<T>::resize (size_t a, size_t b)
// =============================================================================
{
	if (a<=0 || b<=0)	{
		cout<<"Classe     : Matrice                "<<endl ;
		cout<<"Fonction   : changeDimensionTo      "<<endl ;
		cout<<"Erreur (1) : Indices incompatibles  "<<endl ;
		cout<<a<<" / "<<b<<endl ;	
	}
	else	{
		lig  = a ;
		col  = b ;
		dim  = lig*col ;
		delete [] pm ;
		pm = new T  [dim] ;	
		for (size_t i=0;i<dim;i++)
			pm[i]=0.0 ;
	}
	
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

#endif
