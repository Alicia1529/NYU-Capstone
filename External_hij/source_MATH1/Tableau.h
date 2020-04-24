//
//  Tableau.h
//  KNSP_2015
//
//  Created by Jean-Claude Auger on 1/17/15.
//  Copyright (c) 2015 Kyolaris Research Limited. All rights reserved.
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

#ifndef __KNSP_2015__Tableau__
#define __KNSP_2015__Tableau__

// ANSI STL C++ headers
// =============================================================================
#include <vector>

// Project hearders
// =============================================================================
#include "Math1.h"
#include "Liste.h"

// Class Tableau
// =============================================================================
template <class T> class math1::Tableau : public std::vector<T> {
    
private:
    // user input variables
    // =========================================================================
    
    size_t dimt   ;
    size_t dim    ;
    iListe binf   ;
    iListe bsup   ;
    iListe taille ;
    // user output variables
    // =========================================================================
    
public:
    // Coplien canonical class
    // =========================================================================
    Tableau ()                ;
    Tableau (int, int=0, int=0, int=0, int=0, int=0,
                  int=0, int=0, int=0, int=0) ;
    
    Tableau (const Tableau&)     ;
    Tableau<T> & operator =  (const  Tableau<T> &) ;
    ~ Tableau ()                ;
    
    // operator overloading
    // =========================================================================

    
    // =========================================================================
    T& operator ()  (int i1)	{
        size_t k ;
        		if (   i1>=binf(1) && i1<=bsup(1))	{
        k= I_(i1) ;
        		}
        		else	{
        			cout<<"Class Tableau / Operator () 1"<<endl;
        			cout<<setw(10)<<binf(1)<<setw(10)<<bsup(1)<<"|"<<setw(10)<<i1<<endl;
        			k = 0 ;
        			math1::wait() ;
        		}
        
        return this->vector<T>::operator[](k) ;
    }
    
    // =========================================================================
    T& operator ()  (int i1, int i2)	{
        size_t k ;
        if (   i1>=binf(1) && i1<=bsup(1)
            && i2>=binf(2) && i2<=bsup(2) )	{
            k= I_(i1,i2) ;
        }
        else	{
            cout<<endl ;
            cout<<"Class Tableau / Operator () 2"<<endl;
            cout<<setw(10)<<binf(1)<<setw(10)<<bsup(1)<<"|"<<setw(10)<<i1<<endl;
            cout<<setw(10)<<binf(2)<<setw(10)<<bsup(2)<<"|"<<setw(10)<<i2<<endl;
            k = 0 ;
            math1::wait() ;
        }
        
        return this->vector<T>::operator[](k) ;
    }
    
    // =========================================================================
    T& operator ()  (int i1, int i2, int i3)	{
        size_t k ;
        if (   i1>=binf(1) && i1<=bsup(1)
            && i2>=binf(2) && i2<=bsup(2)
            && i3>=binf(3) && i3<=bsup(3) )	{
            k= I_(i1, i2, i3) ;
        }
        else	{
            cout<<endl ;
            cout<<"Class Tableau / Operator () 3"<<endl;
            cout<<setw(10)<<binf(1)<<setw(10)<<bsup(1)<<"|"<<setw(10)<<i1<<endl;
            cout<<setw(10)<<binf(2)<<setw(10)<<bsup(2)<<"|"<<setw(10)<<i2<<endl;
            cout<<setw(10)<<binf(3)<<setw(10)<<bsup(3)<<"|"<<setw(10)<<i3<<endl;
            k = 0 ;
            math1::wait() ;
        }
        
        return this->vector<T>::operator[](k) ;
    }
    
    // =========================================================================
    T& operator ()  (int i1, int i2, int i3, int i4)	{
        size_t k ;
        if (   i1>=binf(1) && i1<=bsup(1)
            && i2>=binf(2) && i2<=bsup(2)
            && i3>=binf(3) && i3<=bsup(3)
            && i4>=binf(4) && i4<=bsup(4) )	{
            k= I_(i1, i2, i3, i4) ;
        }
        else	{
            cout<<endl ;
            cout<<"Class Tableau / Operator () 4"<<endl;
            cout<<setw(10)<<binf(1)<<setw(10)<<bsup(1)<<"|"<<setw(10)<<i1<<endl;
            cout<<setw(10)<<binf(2)<<setw(10)<<bsup(2)<<"|"<<setw(10)<<i2<<endl;
            cout<<setw(10)<<binf(3)<<setw(10)<<bsup(3)<<"|"<<setw(10)<<i3<<endl;
            cout<<setw(10)<<binf(4)<<setw(10)<<bsup(4)<<"|"<<setw(10)<<i4<<endl;
            k = 0 ;
            math1::wait() ;
        }
        
        return this->vector<T>::operator[](k) ;
    }
    
    // =========================================================================
    T& operator ()  (int i1, int i2, int i3, int i4, int i5)	{
        size_t k ;
        if (   i1>=binf(1) && i1<=bsup(1)
            && i2>=binf(2) && i2<=bsup(2)
            && i3>=binf(3) && i3<=bsup(3)
            && i4>=binf(4) && i4<=bsup(4)
            && i5>=binf(5) && i5<=bsup(5) )	{
            k= I_(i1, i2, i3, i4, i5) ;
        }
        else	{
            cout<<endl ;
            cout<<"Class Tableau / Operator () 4"<<endl;
            cout<<setw(10)<<binf(1)<<setw(10)<<bsup(1)<<"|"<<setw(10)<<i1<<endl;
            cout<<setw(10)<<binf(2)<<setw(10)<<bsup(2)<<"|"<<setw(10)<<i2<<endl;
            cout<<setw(10)<<binf(3)<<setw(10)<<bsup(3)<<"|"<<setw(10)<<i3<<endl;
            cout<<setw(10)<<binf(4)<<setw(10)<<bsup(4)<<"|"<<setw(10)<<i4<<endl;
            cout<<setw(10)<<binf(5)<<setw(10)<<bsup(5)<<"|"<<setw(10)<<i5<<endl;
            k = 0 ;
//            math1::wait() ;
        }
        
        return this->vector<T>::operator[](k) ;
    }
    // =========================================================================
    
    
    Tableau<T>& operator =  (const T) ;
    
    size_t I_ (int i1)             {
        return (-binf(1)+i1);
    }
    
    size_t I_(int i1, int i2) {
        return (-binf(1)+i1)*taille(2)+(-binf(2)+i2)  ;
    }
    
    
    size_t I_ (int i1, int i2, int i3)	{
        return (-binf(3)+i3)*taille(1)*taille(2)+I_(i1,i2) ;
    }
    
    size_t I_ (int i1, int i2,int i3, int i4)	{
        return (-binf(4)+i4)*(taille(1)*taille(2)*taille(3))+I_(i1,i2,i3);
    }
    
    size_t I_ (int i1, int i2,int i3, int i4, int i5)	{
        return (-binf(5)+i5)*(taille(1)*taille(2)*taille(3)*taille(4))+I_(i1,i2,i3, i4);
    }
   
    
    // User input function
    // =========================================================================
    
    // User output function
    // =========================================================================
    size_t g_size1()	{return taille(1) ;}
    size_t g_size2()	{return taille(2) ;}
    size_t g_size3()	{return taille(3) ;}
    size_t g_size4()	{return taille(4) ;}
    size_t g_size5()	{return taille(5) ;}
    
    int g_binf1() 	{return binf(1) ;}
    int g_binf2() 	{return binf(2) ;}
    int g_binf3() 	{return binf(3) ;}
    int g_binf4() 	{return binf(4) ;}
    int g_binf5() 	{return binf(5) ;}
    
    int g_bsup1() 	{return bsup(1) ;}
    int g_bsup2() 	{return bsup(2) ;}
    int g_bsup3() 	{return bsup(3) ;}
    int g_bsup4() 	{return bsup(4) ;}
    int g_bsup5() 	{return bsup(5) ;}
    
    size_t g_size()     {return dim;}
    
    // Manipulation function
    // =======================================================================
    // Friend functions
    // =========================================================================
    	template <class V>
       friend std::ostream& operator <<(std::ostream&, Tableau<V>) ;
    
    
private:
    // Internal functions
    // =========================================================================
    
    
} ;
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T>   math1::Tableau<T>::Tableau () : vector<T>(1)
// =============================================================================
{
    Tableau(1) ;
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T> math1::Tableau<T>::
    Tableau (int i1, int i2, int i3, int i4, int i5,
             int i6, int i7, int i8, int i9, int i10) : vector<T>(1)
// =============================================================================
{

    binf.clear() ;
    binf  .resize(5) ;
    bsup  .resize(5) ;
    taille.resize(5) ;
    
    binf(1) = i1 ; binf(2)=i3; binf(3)=i5; binf(4)=i7; binf(5)=i9 ;
    bsup(1) = i2 ; bsup(2)=i4; bsup(3)=i6; bsup(4)=i8; bsup(5)=i10 ;
    
    dimt = 5 ;
    if (i9==0 && i10==0)
        dimt=4;
    if (i7==0 && i8==0)
        dimt=3 ;
    if (i5==0 && i6==0)
        dimt=2 ;
    if (i3==0 && i4==0)
        dimt=1 ;
    
    if (dimt>=1) {
        taille(1) = bsup(1)-binf(1) +1 ;
        dim = taille(1) ;
    }
    
    if (dimt>=2) {
        taille(2) = bsup(2)-binf(2) +1 ;
        dim = taille(1)*taille(2) ;
    }
    
    if (dimt>=3) {
        taille(3) = bsup(3)-binf(3) +1 ;
        dim = taille(1)*taille(2)*taille(3) ;
    }
    
    if (dimt>=4) {
        taille(4) = bsup(4)-binf(4) +1 ;
        dim = taille(1)*taille(2)*taille(3)*taille(4) ;
    }
    
    if (dimt==5) {
        taille(5) = bsup(5)-binf(5) +1 ;
        dim = taille(1)*taille(2)*taille(3)*taille(4)*taille(5) ;
    }
    
    this->resize(dim) ;
    
    
//    cout<<"Binf1"<<endl ;
//    cout<<binf<<endl ;
    
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

template <class T> math1::Tableau<T> :: Tableau (const Tableau &o)
: vector<T> (o)
// =============================================================================
{
    dimt    = o.dimt    ;
    dim     = o.dim     ;
    binf    = o.binf    ;
    bsup    = o.bsup    ;
    taille  = o.taille  ;
    
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

template <class T> math1::Tableau<T>&
math1::Tableau<T>::operator = (const Tableau& o)
// =============================================================================
{
    if (this != &o)	{
        this->vector<T>::operator=(o) ;
        dimt    = o.dimt    ;
        dim     = o.dim     ;
        binf    = o.binf    ;
        bsup    = o.bsup    ;
        taille  = o.taille  ;
    }
    return *this;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T> math1::Tableau<T> :: ~Tableau()
// =============================================================================
{
    
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

    template <class T>
    math1::Tableau<T>& math1::Tableau<T>::operator = (const T o)
// =============================================================================
{
    for (size_t i=1; i<=this->g_size(); i++)
        (*this)(i) = o ;
    return *this;
}

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

 template <class T>
 std::ostream& math1::operator<<(ostream& stream, Tableau<T> t)
 // =============================================================================
 {
     size_t k=0 ;
     stream.precision(9);
     stream << showpoint;
     stream << setiosflags (ios::scientific);
     
     stream <<endl ;
     stream <<"Tableau"<<endl ;
     stream<<"----------------------------"<<endl ;
     stream<<"size           : "<<t.size()<<endl ;
     stream<<"dimt           : "<<t.dimt<<endl ;
     
     stream
     <<setw(5)<<"No"
     <<setw(19)<<"binf"
     <<setw(19)<<"bsup"
     <<setw(19)<<"taille"<<endl ;
     
     for (size_t i=1; i<=t.binf.size(); i++) {
         stream
         <<setw(5)<<i
         <<setw(19)<<t.binf(i)
         <<setw(19)<<t.bsup(i)
         <<setw(19)<<t.taille(i)<<endl ;
     }
     stream<<"----------------------------"<<endl ;
     
     k=-1 ;
     
     switch (t.dimt)	{
         case 1:
             for (int i=t.binf(1);i<=t.bsup(1);i++)	{
                 k++ ;
                 stream
                 <<setw(10)<<k
                 <<setw(10)<<i
                 <<setw(10)<<t.I_(i)
                 <<setw(19)<<t(i)<<endl ;
             }
             break ;
         case 2:
             for (int i=t.binf(1);i<=t.bsup(1);i++)
                 for (int j=t.binf(2);j<=t.bsup(2);j++) {
                     k++ ;
                     stream
                     <<setw(10)<<k
                     <<setw(10)<<i
                     <<setw(10)<<j
                     <<setw(10)<<t.I_(i,j)
                     <<setw(19)<<t(i,j)<<endl ;
                 }
             break ;
         case 3:
             for (int i=t.binf(1);i<=t.bsup(1);i++)	{
                 for (int l=t.binf(3);l<=t.bsup(3);l++){
                 for (int j=t.binf(2);j<=t.bsup(2);j++){
                         k++ ;
                         stream
                         <<setw(10)<<k
                         <<setw(10)<<i
                         <<setw(10)<<j
                         <<setw(10)<<l
                         <<setw(10)<<t.I_(i,j,l)
                         <<setw(19)<<t(i,j,l)<<endl ;
                     }
                 }
             }
             break ;
         case 4:
             for (int n=t.binf(4);n<=t.bsup(4);n++)
                 for (int l=t.binf(3);l<=t.bsup(3);l++)
                     for (int j=t.binf(2);j<=t.bsup(2);j++)
                         for (int i=t.binf(1);i<=t.bsup(1);i++)	{
                             k++ ;
                             stream
                             <<setw(10)<<k
                             <<setw(10)<<i
                             <<setw(10)<<j
                             <<setw(10)<<l
                             <<setw(10)<<n
                             <<setw(10)<<t.I_(i,j,l,n)
                             <<setw(19)<<t(i,j,l,n)<<endl ;
                         }
             break ;
             
         case 5:
             for (int m=t.binf(5);m<=t.bsup(5);m++)
                 for (int n=t.binf(4);n<=t.bsup(4);n++)
                     for (int l=t.binf(3);l<=t.bsup(3);l++)
                         for (int j=t.binf(2);j<=t.bsup(2);j++)
                             for (int i=t.binf(1);i<=t.bsup(1);i++)	{
                                 k++ ;
                                 stream
                                 <<setw(10)<<k
                                 <<setw(10)<<i
                                 <<setw(10)<<j
                                 <<setw(10)<<l
                                 <<setw(10)<<n
                                 <<setw(10)<<m
                                 <<setw(10)<<t.I_(i,j,l,n,m)
                                 <<setw(19)<<t(i,j,l,n,m)<<endl ;
                             }
             break ;
     }

	
	
	
	return stream ;	
 }


// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

#endif /* defined(__KNSP_2015__Tableau__) */
