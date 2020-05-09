/*
 *  tableau.h
 *  iTECHS
 *
 *  Created by Jean Claude Auger on 10/07/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=


// Class TableauX
// =============================================================================
# ifndef TableauX_H
# define TableauX_H

// ANSI STL C++ headers
// =============================================================================
#include <iostream>
#include <math.h>
#include <complex>
#include <iomanip>

// Project hearders
// =============================================================================
#include "Math1.h"

// Name space
// =============================================================================
using namespace std ;

// Class definition
// =============================================================================
template <class T> class math1::TableauX
{
// Variables membres
// =================
private:
T *val ;
size_t dim   ;
int dimt       ;
int dimb   [4] ;
int borne  [8] ;

// Fonctions membres
// =================
public :
// Definition of the canonical class form
// ======================================
 TableauX () ;                                       
 TableauX (int i1  , int i2  , int i3=0, int i4=0,
           int i5=0, int i6=0, int i7=0, int i8=0) ; 
 TableauX (const TableauX&) ;                         
 TableauX<T>& operator = (const TableauX<T>&) ;
~TableauX () ;                                      

// Derivation of operators
// =======================
T& operator() (int i1)                        {
	return val[Idt(i1)]          ;
}

T& operator() (int i1,int i2)                 {
	return val[Idt(i1,i2)]       ;
}

T& operator() (int i1,int i2, int i3)         {
	return val[Idt(i1,i2,i3)]    ;
}

T& operator() (int i1,int i2, int i3, int i4) {
	return val[Idt(i1,i2,i3,i4)] ;
}

TableauX<T>& operator = (const double& r) ;
TableauX<T>& operator = (const cdouble& z) ;

// Fonction des indices sur les tableaux
// =====================================
long int Idt (int i1)             {
	return (-borne[0]+i1);
}

long int Idt (int i1, int i2)     {
	long int k ;
	if ( i1>=borne[0] && i1<=borne[1] && i2>=borne[2] && i2<=borne[3] )	{ 
		k= (-borne[0]+i1+1-1)*(dimb[1])+(-borne[2]+i2) ;
	}
	else	{
		cout<<"Erreur dans la dimension du TableauX"<<endl;
		cout<<i1<<"   "<<i2<<endl;
		k = 0 ;
	}
	return k ;
}

long int Idt (int i1, int i2,int i3)	{ 
	return (long int)(-borne[4]+i3+1-1)*(dimb[0]*dimb[1])+Idt(i1,i2) ;
}

long int Idt (int i1, int i2,int i3, int i4)	{ 
	return (long int)(-borne[6]+i4+1-1)*(dimb[0]*dimb[1]*dimb[2])+Idt(i1,i2,i3);
}


int getBorne1() {
	return borne[0] ;
}
int getBorne2() {
	return borne[1] ;
}
int getBorne3() {
	return borne[2] ;
}
int getBorne4() {
	return borne[3] ;
}
int getBorne5() {
	return borne[4] ;
}
int getBorne6() {
	return borne[5] ;
}
int getBorne7() {
	return borne[6] ;
}
int getBorne8() {
	return borne[7] ;
}

int getDim1()	{
	return dimb[0] ;
}

int getDim2()	{
	return dimb[1] ;
}

int getDim3()	{
	return dimb[2] ;
}

int getDim4()	{
	return dimb[3] ;
}

void changeDimensionTo (int i1  , int i2  , int i3=0, int i4=0,
                               int i5=0, int i6=0, int i7=0, int i8=0) ;

void showObjectInfo () ;
void showObjectValue () ;

friend ostream & operator << (ostream&,TableauX<double> ) ;
friend ostream & operator << (ostream&,TableauX<cdouble > ) ;

};


// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T> math1::TableauX<T>:: TableauX ()
// =================================================
{

for (long int i=0; i<8; i++)
	borne[i] = 0;
dimt = 1 ;

for (long int i=0; i<4; i++)
	dimb[i] = 0;

dim = 1 ;
val = new T [dim] ;
for (long int i=0; i<dim; i++)
	val[i] = 0.0 ;

}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T> math1::TableauX<T>::
        TableauX (int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8)         
// =============================================================================
{

borne[0] = i1 ;
borne[1] = i2 ;
borne[2] = i3 ;
borne[3] = i4 ;
borne[4] = i5 ;
borne[5] = i6 ;
borne[6] = i7 ;
borne[7] = i8 ;

dimt = 4 ;
if (i7==0 && i8==0)
	dimt=3 ;
if (i5==0 && i6==0)
	dimt=2 ;
if (i3==0 && i4==0)
	dimt=1 ;

for (int i=0; i<4; i++)
	dimb[i] = 0;

if (dimt>=1) {
	dimb[0] = borne[1]-borne[0]+1 ; 
	dim = dimb[0] ;
}

if (dimt>=2) { 
	dimb[1] = borne[3]-borne[2]+1 ;
	dim = dimb[0]*dimb[1] ;
}

if (dimt>=3) {
	dimb[2] = borne[5]-borne[4]+1 ;
	dim = dimb[0]*dimb[1]*dimb[2] ;
}

if (dimt==4) {
	dimb[3] = borne[7]-borne[6]+1 ;
	dim = dimb[0]*dimb[1]*dimb[2]*dimb[3] ;
}

val = new T [dim] ;
for (long int i=0; i<dim; i++)
	val[i] = 0.0 ;   
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T> math1::TableauX<T>:: TableauX(const TableauX& t)
// ================================================================
{
borne[0] = t.borne[0] ;
borne[1] = t.borne[1] ;
borne[2] = t.borne[2] ;
borne[3] = t.borne[3] ;
borne[4] = t.borne[4] ;
borne[5] = t.borne[5] ;
borne[6] = t.borne[6] ;
borne[7] = t.borne[7] ;

for (int i=0; i<4; i++)
	dimb[i] = t.dimb[i];
dimt = t.dimt ;
dim  = t.dim  ;
val = new T [dim] ;
for (long int i=0; i<dim; i++)
	val[i] = t.val[i] ;   
} 
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T> math1::TableauX<T>& math1::
                             TableauX<T>:: operator =(const TableauX& t)
// ===================================================================
{

if (this !=&t)	{
	delete [] val ;
   borne[0] = t.borne[0] ;
   borne[1] = t.borne[1] ;
   borne[2] = t.borne[2] ;
   borne[3] = t.borne[3] ;
   borne[4] = t.borne[4] ;
   borne[5] = t.borne[5] ;
   borne[6] = t.borne[6] ;
   borne[7] = t.borne[7] ;
   
	for (int i=0; i<4; i++)
		dimb[i] = t.dimb[i];
   dimt = t.dimt ;
   dim  = t.dim  ;
   val = new T [dim] ;
   for (long int i=0; i<dim; i++)
		val[i] = t.val[i] ;      	
}

return *this ;
}   
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T> math1::TableauX<T>& math1::
                                          TableauX<T>:: operator =(const double& x)
// =============================================================================
{
for (long int i=1;i<dim;i++)
	val[i]=x; 
return *this ;
}   
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T> math1::TableauX<T>& math1::
                                 TableauX<T>:: operator =(const cdouble& z)
// =============================================================================
{
for (long int i=1; i<dim; i++) 
	val[i]=z; 
  return *this ;
}   
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T> math1::TableauX<T>:: ~TableauX ()
// ==================================================
{
//cout<<"DESTRUCTEUR TableauX "<<endl;
   delete [] val ;	
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T> void math1::TableauX<T>:: showObjectInfo ()
// =============================================================
{
cout.precision(9);
cout << showpoint; 
cout << setiosflags (ios::scientific);

cout<<endl ;
cout<<"TableauX"<<endl ;
cout<<"-------"<<endl ;
cout<<setw(9)<<dimt<<endl  ;
cout<<setw(9)<<dim<<endl ;
cout<<"-------"<<endl ;
cout<<setw(5)<<borne[0]<<" "<<setw(5)<<borne[1]<<"   "<<setw(5)<<dimb[0]<<endl ;
cout<<setw(5)<<borne[2]<<" "<<setw(5)<<borne[3]<<"   "<<setw(5)<<dimb[1]<<endl ;
cout<<setw(5)<<borne[4]<<" "<<setw(5)<<borne[5]<<"   "<<setw(5)<<dimb[2]<<endl ;
cout<<setw(5)<<borne[6]<<" "<<setw(5)<<borne[7]<<"   "<<setw(5)<<dimb[3]<<endl ;
cout<<"-------"<<endl ;
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   template <class T> void::math1::TableauX<T>::
   changeDimensionTo (int i1, int i2, int i3, int i4,
                                                 int i5, int i6, int i7, int i8)         
// =============================================================================
{
borne[0] = i1 ;
borne[1] = i2 ;
borne[2] = i3 ;
borne[3] = i4 ;
borne[4] = i5 ;
borne[5] = i6 ;
borne[6] = i7 ;
borne[7] = i8 ;

dimt = 4 ;
if (i7==0 && i8==0)
	dimt=3 ;
if (i5==0 && i6==0)
	dimt=2 ;
if (i3==0 && i4==0)
	dimt=1 ;

for (int i=0;i<4;i++)
	dimb[i] = 0;

if (dimt>=1) {
	dimb[0] = borne[1]-borne[0]+1 ;
	dim = dimb[0] ;
}
if (dimt>=2) { 
	dimb[1] = borne[3]-borne[2]+1 ; 
	dim = dimb[0]*dimb[1] ; 
}
if (dimt>=3) {
	dimb[2] = borne[5]-borne[4]+1 ;
	dim = dimb[0]*dimb[1]*dimb[2] ; 
}
if (dimt==4) {
	dimb[3] = borne[7]-borne[6]+1 ;
	dim = dimb[0]*dimb[1]*dimb[2]*dimb[3] ;
}

delete [] val ;	   
val = new T [dim] ;
for (long int i=0; i<dim; i++)
	val[i] = 0.0 ;
}

#endif