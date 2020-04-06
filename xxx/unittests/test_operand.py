
print("xxx/unittests/test_operand.py")

import os
import sys
path = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir)))

if (not (path in sys.path)) :
    sys.path.append(path)

from operand import DataChunk, Operand


op_e1_bessel1 = Operand("e1.bessel1")
input_chunk1 = DataChunk()
input_chunk1.data = {"n": 0, "z": 1.8 + 0.1j}
op_e1_bessel1.inputs = input_chunk1
op_e1_bessel1.execute()
print(op_e1_bessel1.__dict__)

op_e1_bessel2 = Operand("e1.bessel2")
input_chunk2 = DataChunk()
input_chunk2.data = {"n": 0, "z": 1.8 + 0.1j}
op_e1_bessel2.inputs = input_chunk2
op_e1_bessel2.execute()
print(op_e1_bessel2.__dict__)

op_sum = Operand("+")
input_chunk3 = DataChunk()
for a, b in zip(op_e1_bessel1.outputs, op_e1_bessel2.outputs):
    input_chunk3.data = {"a": a.data, "b": b.data}
    op_sum.inputs.append(input_chunk3)
op_sum.execute()
print(op_sum.__dict__)

