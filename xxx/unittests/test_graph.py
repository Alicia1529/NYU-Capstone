
print("xxx/unittests/test_graph.py")

import os
import sys
path = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir)))

if (not (path in sys.path)) :
    sys.path.append(path)

class Node:
    pass

from operand import DataChunk, Operand
from graph import DirectedGraph

print("-----------Ops-----------")
op_e1_bessel1 = Operand("e1.bessel1")
input_chunk1 = DataChunk()
input_chunk1.data = {"n": 0, "z": 1.8 + 0.1j}
op_e1_bessel1.inputs = input_chunk1
# op_e1_bessel1.execute()
print(op_e1_bessel1.__dict__)

op_e1_bessel2 = Operand("e1.bessel2")
input_chunk2 = DataChunk()
input_chunk2.data = {"n": 0, "z": 1.8 + 0.1j}
op_e1_bessel2.inputs = input_chunk2
# op_e1_bessel2.execute()
print(op_e1_bessel2.__dict__)

op_sum = Operand("+")
input_chunk3 = DataChunk()
# 这里感觉有点问题 因为chunk.key在没有执行operand的情况下无output
# 所以to_dot读不出chunk
for a, b in zip(op_e1_bessel1.outputs, op_e1_bessel2.outputs):
    input_chunk3.data = {"a": a.data, "b": b.data}
    op_sum.inputs.append(input_chunk3)
# op_sum.execute()
print(op_sum.__dict__)

test_graph = DirectedGraph()

# test DirectedGraph.add_node
node1 = Node()
node1.key = 1
node1.op = op_e1_bessel1
test_graph.add_node(node1)

node2 = Node()
node2.key = 2
node2.op = op_e1_bessel2
test_graph.add_node(node2)

node3 = Node()
node3.key = 3
node3.op = op_sum
test_graph.add_node(node3)

print("-----------Nodes-----------")
print(test_graph.get_nodes())

# test DirectedGraph.add_edge
test_graph.add_edge(node1, node3, {"edge":"1 -> 3"})
test_graph.add_edge(node2, node3, {"edge":"2 -> 3"})

# node2 = {"key": 1, "op": op_e1_bessel1 }
# {"key": 1, "op": op_e1_bessel1}
# test_graph.add_node(1, node1)
# node2 = {"key": 2, "op": op_e1_bessel2 }
# test_graph.add_node(2, node2)
# node3 = {"key": 3, "op": op_sum}
# test_graph.add_node(3, node3)

print("-----------To dot-----------")
to_dot = test_graph.to_dot()
print(to_dot)
