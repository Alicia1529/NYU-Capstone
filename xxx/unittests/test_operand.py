
print("xxx/unittests/test_operand.py")

import os
import sys
path = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir)))


if (not (path in sys.path)) :
    sys.path.append(path)

print(sys.path)
print(os.path.dirname(__file__))
print(os.path.pardir)
from operand import Operand


op_e1_bessel1 = Operand("e1.bessel1")
op_e1_bessel1.inputs = {"n": 0, "z": 1.8 + 0.1j}
op_e1_bessel1.execute()
print(op_e1_bessel1.__dict__)

op_e1_bessel2 = Operand("e1.bessel2")
op_e1_bessel2.inputs = {"n": 0, "z": 1.8 + 0.1j}
op_e1_bessel2.execute()
print(op_e1_bessel2.__dict__)

op_sum = Operand("+")
op_sum.inputs = {"a": op_e1_bessel1.outputs, "b": op_e1_bessel2.outputs}
op_sum.execute()
print(op_sum.__dict__)

