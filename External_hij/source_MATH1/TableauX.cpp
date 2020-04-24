/*
 *  tableau.cpp
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

// ANSI MSL C++ classes
// =============================================================================

// Project classes
// =============================================================================
#include "TableauX.h"

namespace math1{
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   ostream& operator <<(ostream& stream, TableauX<double> t )
// =============================================================
{
	long int k=0 ;
	stream.precision(9);
	stream << showpoint; 
	stream << setiosflags (ios::scientific);
	
	stream<<"Matrix values"<<endl;
	stream<<"-------------"<<endl;
	t.showObjectInfo() ;
	
	k=-1 ;  
	switch (t.dimt)	{
		case 1:
			for (int i=t.borne[0];i<=t.borne[1];i++)	{
				k++ ;
				stream
                <<setw(5)<<k<<setw(5)<<i<<setw(6)<<t.Idt(i)
                <<setw(19)<<t.val[t.Idt(i)]<<endl ;	
			}
			break ;
		case 2:
			for (int i=t.borne[0];i<=t.borne[1];i++)
				for (int j=t.borne[2];j<=t.borne[3];j++)	{
					k++ ;
					stream<<setw(5)<<k<<" "<<setw(5)<<i<<" "<<setw(5)<<j<<" "
						<<setw(5)<<t.Idt(i,j)<<" "<<setw(19)<<t.val[t.Idt(i,j)]<<endl ;
				}
					break ;
		case 3:
			for ( int l=t.borne[4];l<=t.borne[5];l++)
				for ( int i=t.borne[0];i<=t.borne[1];i++)
					for ( int j=t.borne[2];j<=t.borne[3];j++)		  {
						k++ ;
						stream<<setw(5)<<k<<" "<<setw(5)<<i<<" "<<setw(5)<<j<<" "
							<<setw(5)<<l<<" "<<setw(5)<<t.Idt(i,j,l)<<" "
							<<setw(19)<<t.val[t.Idt(i,j,l)]<<endl ;	
					}
						break ;
		case 4:
			for ( int n=t.borne[6];n<=t.borne[7];n++)
				for ( int l=t.borne[4];l<=t.borne[5];l++)
					for ( int i=t.borne[0];i<=t.borne[1];i++)
						for ( int j=t.borne[2];j<=t.borne[3];j++)
						{
							k++ ;
							stream<<setw(5)<<k<<" "<<setw(5)<<i<<" "<<setw(5)<<j<<" "
								<<setw(5)<<l<<" "<<setw(5)<<n<<" "<<setw(5)<<t.Idt(i,j,l,n)<<" "
								<<setw(19)<<t.val[t.Idt(i,j,l,n)]<<endl ;	
						}  	
							break ;
	}
	
	return stream ;
}		
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

   ostream& operator <<(ostream& stream, TableauX<cdouble > t )
// ========================================================================
{
	long int k=0 ;
	stream.precision(9);
	stream << showpoint; 
	stream << setiosflags (ios::scientific);
	
	stream<<"Matrix values"<<endl;
	stream<<"-------------"<<endl;
	t.showObjectInfo() ;
	
	k=-1 ;  
	switch (t.dimt)	{
		case 1:
			for ( int i=t.borne[0];i<=t.borne[1];i++)	{
				k++ ;
				stream<<setw(5)<<k<<" "<<setw(5)<<i<<" "<<setw(5)<<t.Idt(i)<<" "
					<<setw(19)<<real(t.val[t.Idt(i)])<<" "
					<<setw(19)<<imag(t.val[t.Idt(i)])<<endl;
				
			}
			break ;
		case 2:
			for ( int i=t.borne[0];i<=t.borne[1];i++)
				for ( int j=t.borne[2];j<=t.borne[3];j++)	{
					k++ ;
					stream<<setw(5)<<k<<" "<<setw(5)<<i<<" "<<setw(5)<<j<<" "
						<<setw(5)<<t.Idt(i,j)<<" "
						<<setw(19)<<real(t.val[t.Idt(i,j)])<<" "
						<<setw(19)<<imag(t.val[t.Idt(i,j)])<<endl;
				}
					break ;
		case 3:
			for ( int l=t.borne[4];l<=t.borne[5];l++)
				for ( int i=t.borne[0];i<=t.borne[1];i++)
					for ( int j=t.borne[2];j<=t.borne[3];j++)		  {
						k++ ;
						stream<<setw(5)<<k<<" "<<setw(5)<<i<<" "<<setw(5)<<j<<" "
							<<setw(5)<<l<<" "<<setw(5)<<t.Idt(i,j,l)<<" "
							<<setw(19)<<real(t.val[t.Idt(i,j,l)])<<" "
							<<setw(19)<<imag(t.val[t.Idt(i,j,l)])<<endl;
					}
						break ;
		case 4:
			for ( int n=t.borne[6];n<=t.borne[7];n++)
				for ( int l=t.borne[4];l<=t.borne[5];l++)
					for ( int i=t.borne[0];i<=t.borne[1];i++)
						for ( int j=t.borne[2];j<=t.borne[3];j++)	{
							k++ ;
							stream<<setw(5)<<k<<" "<<setw(5)<<i<<" "<<setw(5)<<j<<" "
								<<setw(5)<<l<<" "<<setw(5)<<n<<" "<<setw(5)<<t.Idt(i,j,l,n)
								<<" "<<setw(19)<<real(t.val[t.Idt(i,j,l,n)])<<" "
								<<setw(19)<<imag(t.val[t.Idt(i,j,l,n)])<<endl;
						}  	
							break ;
	}
	
	return stream ;
}		
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

template <> void math1::TableauX<double> :: showObjectValue ()
// ============================================================
{
	cout<<*this ;
} 
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

template <> void math1::TableauX<cdouble > :: showObjectValue ()
// =====================================================================
{
	cout<<*this ;
} 
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

	void testTableauX ()
// =============================================================================
{
	
	cout<<"	Programme LSC : Teste de la classe: TableauX "<<endl ;
	cout<<" ============================================"<<endl ;
	cout<<" "<<endl ;
	
}
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
//
// =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
}
