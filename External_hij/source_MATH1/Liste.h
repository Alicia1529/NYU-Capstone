//
//  Liste.h
//  KNSP_2015
//
//  Created by Jean-Claude Auger on 1/17/15.
//  Copyright (c) 2015 Kyolaris Research Limited. All rights reserved.
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

#ifndef __KNSP_2015__Liste__
#define __KNSP_2015__Liste__

// ANSI STL C++ headers
// =============================================================================

#include <valarray>
#include <vector>
#include <iostream>
#include <iomanip>
#include <complex>

#include <algorithm>

#include <typeinfo>
// Project hearders
// =============================================================================
#include "Math1.h"

// Class Liste
// =============================================================================

template <class T> class math1::Liste : public std::vector<T> {
    
protected:
    // user input variables
    // =========================================================================

    // user output variables
    // =========================================================================
    
public:
    // Coplien canonical class
    // =========================================================================
    Liste ()                             ;
    Liste (size_t, T = 0.0)              ;
    Liste (const Liste&)                 ;
    Liste<T>& operator=(const Liste<T>&) ;
    ~ Liste ()                ;
    
    // operator overloading
    // =========================================================================
    T& operator ()  (size_t i)	{
        
        if (i>=1 && i<=this->size()) {
            return this->vector<T>::operator[](i-1) ;
        }
        else {
            cout<<"Class : Liste"<<endl ;
            cout<<"Fonction: operator() "<<endl ;
            cout<<"Erreur  : Erreur indice"<<endl ;
            cout<<"Min is    : 1"<<endl ;
            cout<<"Max is    : "<<setw(5)<<this->size()<<endl ;
            cout<<"Given was : "<<setw(5)<<i<<endl ;
//            math1::wait() ;
            
        }
        return this->vector<T>::operator[](1) ;
    }
    
    Liste<T>& operator =  (const T) ;
    Liste<T>& operator =  (const vector<T>&) ;
    
    // User input function
    // =========================================================================
    void liste_reverse () {reverse(this->begin(),this->end());}
    void liste_sort    () {sort   (this->begin(),this->end());}
    void liste_rsort   () {liste_sort() ; liste_reverse() ;}
    
    void resize0 (size_t n) {this->std::vector<T>::operator=(vector<T>(n)) ;}
    
    
    // User output function
    // =========================================================================
    bool valueIsInMatrix(T) ;
    
    T    trace            () ;
    T g_min(size_t&) ;
    T g_max(size_t&) ;
   
    
    double  module  (double & x) { return x            ; }
    double  module  (cdouble& z) { return std::norm(z) ; }
    
    bool onlyHasStrictlyPositiveValue() ;
    bool onlyHasZeroOrPositiveValue() ;
    
    
    // Manipulation function
    // =======================================================================
    
    // Friend functions
    // =========================================================================
 //   template <typename V> friend std::ostream& operator <<(std::ostream&, Matrix<V>);
    
private:
    // Internal functions
    // =========================================================================
    
    
} ;
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T> math1::Liste<T>:: Liste (): vector<T>()
// =============================================================================
{

}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T> math1::Liste<T>::Liste (size_t i, T x): vector<T>(i)
// =============================================================================
{
    for (size_t j=1; j<=this->size(); j++)
        (*this)(j) = x ;
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T> math1::Liste<T>::Liste (const Liste &o): vector<T>(o)
// =============================================================================
{

}
 
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T>
    math1::Liste<T>& math1::Liste<T>::operator = (const Liste& o)
// =============================================================================
{
    if (this != &o)	{
        this->vector<T>::operator=(o) ;
    }
    return *this;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T>
    math1::Liste<T>& math1::Liste<T>::operator = (const T o)
// =============================================================================
{

    for (size_t i=1; i<=this->size(); i++)
        (*this)(i) = o ;
    
    return *this;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T>
    math1::Liste<T>& math1::Liste<T>::operator = (const vector<T>& o)
// =============================================================================
{
    this->vector<T>::operator=(o) ;
    
    return *this;
}


// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T> math1::Liste<T> :: ~ Liste()
// =============================================================================
{
    
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T>
    bool math1::Liste<T>::valueIsInMatrix(T val)
// =============================================================================
{
    // =========================================================================
    bool res = false ;
    // =========================================================================

    for (size_t i=1; i<=this->size(); i++)
        if ((*this)(i)==val)
            res = true ;

    return res ;
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T>
    T math1::Liste<T>::g_min(size_t& indicem)
// =============================================================================
{
    // =========================================================================
    T minv ;
    // =========================================================================
    
    minv    = module((*this)(1)) ;
    indicem = 1                  ;
    
    for (size_t i=2; i<=this->size(); i++)
        if ( module((*this)(i))<minv )	{
            minv    = module((*this)(i)) ;
            indicem = i                  ;
        }
    
    return minv ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T>
    T math1::Liste<T>:: g_max(size_t& indicem)
// =============================================================================
{
    // =========================================================================
    T maxv ;
    // =========================================================================

    maxv    = module((*this)(1)) ;
    indicem = 1                  ;
    
    for (size_t i=2; i<=this->size(); i++)
        if ( module((*this)(i))>maxv )	{
            maxv = module((*this)(i)) ;
            indicem = i ;
        }
    
    return maxv ;
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T> T math1::Liste<T>::trace()
// =============================================================================
{
    T res=0.0 ;
    
    for (size_t i=1; i<=this->size(); i++)
        res +=  (*this)(i) ;
    

    return res ;
}

#endif /* defined(__KNSP_2015__Liste__) */