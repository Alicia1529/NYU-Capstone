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
#include <string>
#include <time.h>
#include "Math1.h"
#include "VectorialTranslationalMatrix.h"

// ============================================================================

// using namespace std;
// extern "C"{
// int hij(){
//     cout.precision(9) ;
//     cout.setf(ios::scientific)             ;
//     cout.setf(ios::showpoint)              ;

//     cout.precision(9) ;
//     cout.setf(ios::scientific)             ;
//     cout.setf(ios::showpoint)              ;

//     double pi=4.0*atan(1.0) ;
//     double p,t ;
//     cdouble z ;
//     int nmax ;

//     p = 0.05 ;
//     z = cdouble (p,0.0) ;
//     t = 30.0/180*pi   ;
//     p = 130.0/180*pi   ;
//     nmax = 4;
//     TranslationTheoremAlgorithm mode1 = brian3Y ;

//     cout<<" nmax = "<< nmax << endl ;
//     cout<<" z    = "<< z    << endl ;
//     cout<<" t    = "<< t    << endl ;
//     cout<<" p    = "<< p    << endl ;

//     cMatrice ret;
//     VectorialTranslationalMatrix hij;

//     hij.g_HMatrix (ret, nmax, nmax, z,t,p, mode1) ;

//     size_t row = ret.g_lig();
//     size_t col = ret.g_col();
//     for (int i = 0; i < row * col; i++) {
//         cdouble each = ret.g_pm()[i];
//         cout << "num " << i << ": " << each << endl;
//     }
//     return 0;
// }
// }

// =============================================================================

using namespace std ;

int main(int argc, const char * argv[]) {
    clock_t start, end;
    start = clock();

    ofstream outfile("../data/test2.txt");

    cout.precision(9) ;
    cout.setf(ios::scientific)             ;
    cout.setf(ios::showpoint)              ;

    cout.precision(9) ;
    cout.setf(ios::scientific)             ;
    cout.setf(ios::showpoint)              ;
// =============================================================================

    double pi = 4.0 * atan(1.0) ;
    double p,t ;
    cdouble z ;
    int nmax ;

    p = 0.05 ;
    z = cdouble (p,0.0) ;
    t = 30.0/180*pi   ;
    p = 130.0/180*pi   ;
    nmax = 14;
    TranslationTheoremAlgorithm mode1 = brian3Y ;

//    outfile <<" nmax = "<< nmax << endl ;
//    outfile <<" z    = "<< z    << endl ;
//    outfile <<" t    = "<< t    << endl ;
//    outfile <<" p    = "<< p    << endl ;

    cMatrice ret;
    VectorialTranslationalMatrix hij;

    hij.g_HMatrix (ret, nmax, nmax, z,t,p, mode1) ;

    size_t row = ret.g_lig();
    size_t col = ret.g_col();
    for (int i = 0; i < row * col; i++) {
        cdouble each = ret.g_pm()[i];
        outfile << "num " << i << ": " << each << endl;
    }

    end = clock();
    cout << double(end-start)/CLOCKS_PER_SEC << endl;
    
    return 0;
}

