//
//  main.cpp
//  EXE_KNSPv2.1
//
//  Created by Jean-Claude Auger on 12/25/15.
//  Copyright © 2015 Kyolaris Research Limited. All rights reserved.
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

#include <iostream>

#include "Math1.h"
#include "VectorialTranslationalMatrix.h"



// ============================================================================
#include<string>
using namespace std;
extern "C"{
int hij(){
    cout.precision(9) ;
    cout.setf(ios::scientific)             ;
    cout.setf(ios::showpoint)              ;

    using namespace math1;
    cout.precision(9) ;
    cout.setf(ios::scientific)             ;
    cout.setf(ios::showpoint)              ;
// =============================================================================


    double pi=4.0*atan(1.0) ;
    double p,t ;
    cdouble z ;
    int nmax ;

    p = 0.05 ;
    z = cdouble (p,0.0) ;
    t = 30.0/180*pi   ;
    p = 130.0/180*pi   ;
    nmax = 4;
    TranslationTheoremAlgorithm mode1 = brian3Y ;

    cout<<" nmax = "<< nmax << endl ;
    cout<<" z    = "<< z    << endl ;
    cout<<" t    = "<< t    << endl ;
    cout<<" p    = "<< p    << endl ;

//	z = cdouble(1.0,0.0) ;
    cMatrice ret;
    VectorialTranslationalMatrix hij;

    hij.g_HMatrix (ret, nmax, nmax, z,t,p, mode1) ;

    size_t row = ret.g_lig();
    size_t col = ret.g_col();
    for (int i = 0; i < row * col; i++) {
        cdouble each = ret.g_pm()[i];
        cout << "num " << i << ": " << each << endl;
    }
    return 0;
}
}

// =============================================================================
//void MainMenu () ;
//void ValidationSWIG() ;
//
//using namespace std ;
//
//
//
//int main(int argc, const char * argv[]) {
//
//    MainMenu () ;
//    return 0;
//}
//
//
//
//// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
////
//// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
//void MainMenu ()
//// =============================================================================
//{
//// =============================================================================
//    cout.precision(9) ;
//    cout.setf(ios::scientific)             ;
//    cout.setf(ios::showpoint)              ;
//// =============================================================================
//
//    using namespace math1;
//
//    double pi=4.0*atan(1.0) ;
//    double p,t ;
//    cdouble z ;
//    int nmax ;
//
//    p = 0.05 ;
//    z = cdouble (p,0.0) ;
//    t = 30.0/180*pi   ;
//    p = 130.0/180*pi   ;
//    nmax = 4;
//    TranslationTheoremAlgorithm mode1 = brian3Y ;
//
//    cout<<" nmax = "<< nmax << endl ;
//    cout<<" z    = "<< z    << endl ;
//    cout<<" t    = "<< t    << endl ;
//    cout<<" p    = "<< p    << endl ;
//
////	z = cdouble(1.0,0.0) ;
//    cMatrice ret;
//    VectorialTranslationalMatrix hij;
//
//    hij.g_HMatrix (ret, nmax, nmax, z,t,p, mode1) ;
//
//    size_t row = ret.g_lig();
//    size_t col = ret.g_col();
//    for (int i = 0; i < row * col; i++) {
//        cdouble each = ret.g_pm()[i];
////        cout << "num " << i << ", real: " << each.__re_ << ", imag: " << each.__im_ << endl;
//    }
//
//
//}
//
//
//
//
