// Example program
#include <iostream>
#include <string>
#include <complex>
#include <complex.h>

int main()
{
  complex<double> z = 1.8 + 0.1I;
  complex<double> j = 4.211104716e-13 + 4.092815803e-13I;
  auto zj = z *j;
  std::cout << creal(zj);
  std::cout << cimag(zj);
}

// c++ output
// j (4.2111e-13,4.09282e-13)
// 7.17071e-13
// 7.78818e-13

// python output
// >>> z = 1.8+0.1j
// >>> z 
// (1.8+0.1j)
// >>> z* 4.211104716e-13
// (7.5799884888e-13+4.2111047160000004e-14j)
// >>> z* (4.211104716e-13 + 4.092815803e-13j)
// (7.1707069085e-13+7.788178917e-13j)