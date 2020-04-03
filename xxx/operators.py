print("xxx/operators.py")

# a file to store all the operators

import os
import sys
path = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir)))
if (not (path in sys.path)) :
    sys.path.append(path)

import Validation_Code.E_AllBesselSpherical1 as e1
import Validation_Code.E_AllBesselSpherical2 as e2

def customized_sum(a, b):
    return a + b

def customized_multiply(a, b):
    return a * b

op_dict = {
    "+": customized_sum,
    "*": customized_multiply,
    "e1.bessel1": e1.bessel1,
    "e1.bessel2": e1.bessel2,
    "e2.bessel1": e2.bessel1,
    "e2.bessel2": e2.bessel2,
}