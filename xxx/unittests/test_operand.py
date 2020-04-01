
print("xxx/unittests/test_operand.py")

import os
import sys
path1 = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir)))

path2 = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir, os.path.pardir)))

if (not (path1 in sys.path)) :
    sys.path.append(path1)
if (not (path2 in sys.path)) :
    sys.path.append(path2)

print(sys.path)
print(os.path.dirname(__file__))
print(os.path.pardir)
from operand import Operand

from Validation_Code.E_AllBesselSpherical1 import *

print(bessel3(3,4))


op1 = Operand("bessel")
op1.inputs = {"n":3, "z": 4}
op1.outputs = {"output1": bessel3(3, 4)}

print(op1.__dict__)

a = bessel1(3, 4)
b = bessel1(3, 4)
c = bessel1(a, b)
