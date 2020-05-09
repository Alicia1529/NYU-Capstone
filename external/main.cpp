//
//  main.cpp
//  EXE_KNSPv2.1
//
//  Created by Jean-Claude Auger on 12/25/15.
//  Copyright © 2015 Kyolaris Research Limited. All rights reserved.
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=]

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Math1.h"
#include "VectorialTranslationalMatrix.h"

// =============================================================================

using namespace std ;

int main(int argc, const char * argv[]) {
    clock_t start, end;
    start = clock();

    ifstream infile("external/input_data/hij_input.txt");
    string line;
    getline(infile, line);
    int nmax = stoi(line);
    getline(infile, line);
    int nbp = stoi(line);
    getline(infile, line);
    double lbd = stod(line);
    getline(infile, line);
    double n0 = stod(line);

    int i, j;
    double tmp;
    string token;
    vector<vector<double>> v;
    for (i = 0; i < nbp; i++) {
        getline(infile, line);
        stringstream ss(line);
        vector<double> c;
        for (j = 0; j < 3; j++) {
            getline(ss, token, ' ');
            tmp = stod(token);
            c.push_back(tmp);
        }
        v.push_back(c);
    }

// =============================================================================

    double x1, y1, z1;
    dMatrice dij(nbp, nbp), thetaij(nbp, nbp), phiij(nbp, nbp);
    for (i = 1; i <= nbp; i++) {
        for (j = 1; j <= nbp; j++) {
            if (i != j) {
                x1 = v[j-1][0] - v[i-1][0];
                y1 = v[j-1][1] - v[i-1][1];
                z1 = v[j-1][2] - v[i-1][2];
                math1::transformCartesianToSphericalCoordinate
                        (x1, y1, z1, dij(i,j), thetaij(i,j), phiij(i,j)) ;
            }
        }

    }

// =============================================================================
    cout.precision(9) ;
    cout.setf(ios::scientific)             ;
    cout.setf(ios::showpoint)              ;

    cout.precision(9) ;
    cout.setf(ios::scientific)             ;
    cout.setf(ios::showpoint)              ;
// =============================================================================
    double t, p;
    double pi = 4.0 * atan(1.0) ;

//    int rr = 1;
//    int cc = 2;
    for (int rr = 1; rr <= nbp; rr++) {
        for (int cc = 1; cc <= nbp; cc++) {
            string dir = "external/data/H(" + to_string(rr) + "," + to_string(cc) + ")_.txt";
            ofstream outfile(dir, ios::out);

            p = 2.0 * dij(rr, cc) * pi * n0 / lbd; // kdij
            cdouble z = cdouble (p,0.0) ;
            t = thetaij(rr, cc);
            p = phiij(rr, cc)  ; // phi
            TranslationTheoremAlgorithm mode1 = brian3Y ;
            outfile << "kd \t theta \t phi" << endl;
            outfile << p << "\t" << t << "\t" << z << "\t" << endl;

            outfile << "----------------------------" << endl;
            outfile << endl;

            cMatrice ret;
            VectorialTranslationalMatrix hij;

            hij.g_HMatrix (ret, nmax, nmax, z,t,p, mode1) ;
            size_t row = ret.g_lig();
            size_t col = ret.g_col();

            for (i = 0; i < row * col; i++) {
                cdouble each = ret.g_pm()[i];
                outfile << scientific << setprecision(10) << i+1 << "\t"
                << each.real() << "\t" << each.imag() << endl;
            }
            outfile.close();
        }
    }

    for (int rr = 1; rr <= nbp; rr++) {
        for (int cc = 1; cc <= nbp; cc++) {
            string dir = "external/data/J(" + to_string(rr) + "," + to_string(cc) + ")_.txt";
            ofstream outfile(dir, ios::out);

            p = 2.0 * dij(rr, cc) * pi * n0 / lbd; // kdij
            cdouble z = cdouble (p,0.0) ;
            t = thetaij(rr, cc);
            p = phiij(rr, cc)  ; // phi
            TranslationTheoremAlgorithm mode1 = brian3Y ;
            outfile << "kd \t theta \t phi" << endl;
            outfile << p << "\t" << t << "\t" << z << "\t" << endl;

            outfile << "----------------------------" << endl;
            outfile << endl;

            cMatrice ret;
            VectorialTranslationalMatrix hij;

            hij.g_JMatrix (ret, nmax, nmax, z,t,p, mode1) ;
            size_t row = ret.g_lig();
            size_t col = ret.g_col();

            for (i = 0; i < row * col; i++) {
                cdouble each = ret.g_pm()[i];
                outfile << scientific << setprecision(10) << i+1 << "\t"
                        << each.real() << "\t" << each.imag() << endl;
            }
            outfile.close();
        }
    }

    end = clock();
    // cout << double(end-start)/CLOCKS_PER_SEC << endl;

    return 0;
}