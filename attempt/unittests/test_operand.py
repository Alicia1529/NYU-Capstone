
print("xxx/unittests/test_operand.py")

import os
import sys
path = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir)))

if (not (path in sys.path)) :
    sys.path.append(path)

from operand import DataChunk, Operand


op_e1_bessel1 = Operand("e1.bessel1")
op_e1_bessel1.inputs = {"n": DataChunk(0), "z": DataChunk(1.8 + 0.1j)}
op_e1_bessel1.execute()
print(op_e1_bessel1.__dict__)

op_e1_bessel2 = Operand("e1.bessel2")
op_e1_bessel2.inputs = {"n": DataChunk(0), "z": DataChunk(1.8 + 0.1j)}
op_e1_bessel2.execute()
print(op_e1_bessel2.__dict__)

op_sum = Operand("+")
op_sum.inputs = {"a": op_e1_bessel1.outputs, "b": op_e1_bessel2.outputs}
op_sum.execute()
print(op_sum.__dict__)
print("output:", op_sum.outputs.__dict__)
