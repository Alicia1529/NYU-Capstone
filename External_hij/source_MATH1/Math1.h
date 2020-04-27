/*
 *  baseFunction.h
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


// NAMESPACE MATH1
// =============================================================================
#ifndef MATH1_
#define MATH1_

// ANSI STL C++ headers
// =============================================================================
#include <vector>
#include <iostream>
#include <complex>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <math.h>
#include <fstream>
#include <string>

// Project hearders
// =============================================================================



namespace  math1
{
    using namespace std ;
    
//==============================================================================
//==============================================================================
//
//          CONSTANT
//
//==============================================================================
//==============================================================================
    
    
    // Constante
    // =============================================================================
    
    //    const string path_      = "/Users/jca/Kyo_data/KNSPv2/" ;

//==============================================================================
//
//              DEFINITION DE TOUTES LES CLASSES DE CONTAINERS
//
//==============================================================================
    
    void Menu () ;
    
    // Constant
    // =========================================================================
    const int streamPrecision = 9   ;
    const int dimFactorielMax = 171 ;

    
    // Class validation math1
    // =========================================================================
    
    typedef complex<double> cdouble ;
    
    
    // Template class Tableau
    // =========================================================================
    template <class T> class Tableau    ;
    
    typedef Tableau<int>              iTableau ;
    typedef Tableau<long int>         lTableau ;
    typedef Tableau<double>           dTableau ;
    typedef Tableau<cdouble > cTableau ;
    
    template <class T> ostream& operator<< (ostream&, Tableau<T> ) ;
    void testTableau () ;
    
    // Template class Matrice
    // =========================================================================
    template <class T> class Matrice    ;
    
    typedef Matrice<int> iMatrice ;
    typedef Matrice<double> dMatrice ;
    typedef Matrice<cdouble > cMatrice ;

     void testMatrice () ;
    
    
    template <class T> class Liste    ;
    
    typedef Liste<size_t>           sListe ;
    typedef Liste<long int>         lListe ;
    typedef Liste<int>              iListe ;
    typedef Liste<double>           dListe ;
    typedef Liste<complex<double> > cListe ;

    
    // Template class Tableau
    // =============================================================================
    template <class T> class TableauX    ;
    
    
    
    // Enumaration type TranslationTheoremAlgorithm
	// =============================================================================
    enum TranslationTheoremAlgorithm {
        chewRecursif,
        brian3Y
    } ;

 	
	// Maths functions
	// =============================================================================
	double mun  (long int) ; 
	double fa   (int) ; 
	double lnfa (int) ;
	double ffa  (int) ;
	double Log2(double)	;
	long int fix(double) ;
	bool isOdd  (int)   ;
	bool isEven (int)  ; 
	cdouble ipn (int) ;
    
    bool isOdd  (size_t)   ;
    bool isEven (size_t)  ;


	dTableau g_FactorialInArray    (int n=dimFactorielMax) ;
	dTableau g_LogFactorialInArray (int n=dimFactorielMax) ;

	
	// Changement de base
	// =============================================================================

    // Random number generator
    // =============================================================================
 	
	// Fonctions de conversion
	// =============================================================================

	// Fonctions d'erreur
	// =============================================================================
	template<typename T>	inline bool isnan(T value)	{
		return value != value;
	}																
	
	template<typename T>	inline bool isinf(T value)	{
		return std::numeric_limits<T>::has_infinity &&
		value == std::numeric_limits<T>::infinity() ;
	}			
	
 

 	
    // Class Vector3D
	// =============================================================================
	template <class T> class Vector3D   ;

	typedef Vector3D<cdouble > cVector3D ;
    typedef Vector3D<double>           dVector3D ;

    ostream& operator<< (ostream&, cVector3D ) ;
    ostream& operator<< (ostream&, dVector3D ) ;

    
    // Polynome de Legendre
    // =============================================================================
    class     AssociatedLegendreFunction   ;
    void  testAssociatedLegendreFunction() ;
    ostream& operator<< (ostream&, AssociatedLegendreFunction ) ;
    
    
    // Bessel Spherical
    // =============================================================================
    class     BesselSpherical   ;
    void  testBesselSpherical() ;
    ostream& operator<< (ostream&, BesselSpherical ) ;
    
 
    // SphericalWaveBasis
    // =============================================================================
    class     SphericalWaveBasis   ;
    void  testSphericalWaveBasis() ;
    ostream& operator<< (ostream&, SphericalWaveBasis ) ;

    // ScalarTranslationalMatrix
    // =============================================================================
    class     ScalarTranslationalMatrix   ;
    void  testScalarTranslationalMatrix() ;
    ostream& operator<< (ostream&, ScalarTranslationalMatrix ) ;
    
    // ScalarTranslationalMatrix
    // =============================================================================
    class     VectorialTranslationalMatrix   ;
    void  testVectorialTranslationalMatrix() ;
    ostream& operator<< (ostream&, VectorialTranslationalMatrix ) ;

    
    
    
    
    
    // Function
    // =============================================================================
    void wait() ;
    void wait(string) ;
    
    

    
    // Classe de base
    // =============================================================================
    class     BaseClass   ;
    void  testBaseClass() ;
    
    void transformCartesianToSphericalCoordinate
            (double, double, double, double&, double&, double&);

    template <class T> void saveObjectToFile (string, T&, const string) ;

} ;










// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

template <class T>
void math1::saveObjectToFile (string nom, T& object, string  display_)
// =============================================================================
{
    ofstream  ecri1     ;
    const char *pnomf   ;
    
    // Etape 1: lecture des parametres depuis le fichier source
    // ========================================================
    //	object.setDisplayTo(formatd) ;
    pnomf  = nom.data() ;
    ecri1.open (pnomf)        ;
    if (ecri1.is_open())	{
        object.s_DISPLAY(display_) ;
        ecri1<<object ;
        ecri1.close() ;
    }
    else	{
        cout<<"namespace: base"<<endl;
        cout<<"fonction : saveObjectToFile (stmf)"<<endl;
        cout<<"erreur   : Impossible de creer le fichier"<<endl;
        cout<<"Given file name was : "<<nom<<endl<<endl ;
        math1::wait() ;
    }
    
    
    
    
}



#endif


