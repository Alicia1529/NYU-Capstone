
print("xxx/unittests/test_graph.py")

import os
import sys
import time
path = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir)))

if (not (path in sys.path)) :
    sys.path.append(path)

class Node(object):
    def __init__(self, op):
        self.key = str(hash(time.time()))
        self.op = op
        self._op_name = op.op_name 

from operand import DataChunk, Operand

from graph import DirectedGraph

print("-----------Ops-----------")
op_e1_bessel1 = Operand("e1.bessel1")
op_e1_bessel1.inputs = {"n": DataChunk(0), "z": DataChunk(1.8 + 0.1j)}
# op_e1_bessel1.execute()
print(op_e1_bessel1.__dict__)

op_e1_bessel2 = Operand("e1.bessel2")
op_e1_bessel2.inputs = {"n": DataChunk(0), "z": DataChunk(1.8 + 0.1j)}
# op_e1_bessel2.execute()
print(op_e1_bessel2.__dict__)

op_sum = Operand("+")
op_sum = Operand("+")
op_sum.inputs = {"a": op_e1_bessel1.outputs, "b": op_e1_bessel2.outputs}
# op_sum.execute()
print(op_sum.__dict__)

test_graph = DirectedGraph()

# test DirectedGraph.add_node
node1 = Node(op_e1_bessel1)
test_graph.add_node(node1)

node2 = Node(op_e1_bessel2)
test_graph.add_node(node2)

node3 = Node(op_sum)
test_graph.add_node(node3)

print("\n-----------Nodes-----------")
nodes = test_graph.get_nodes()
for node in nodes:
    print(node.__dict__)

# test DirectedGraph.add_edge
test_graph.add_edge(node1, node3, {"edge":"1 -> 3"})
test_graph.add_edge(node2, node3, {"edge":"2 -> 3"})

print("\n-----------To dot-----------")
to_dot = test_graph.to_dot()
print(to_dot)

print("\n-----------view-----------")
test_graph.view()

print("\n-----------traverse----------")
traverse = test_graph.traverse()
for node in traverse:
    print(node.__dict__, node.op.__dict__)

print("\n-----------dfs----------")
dfs = test_graph.dfs()
for node in dfs:
    print(node.__dict__, node.op.__dict__)

print("\n-----------bfs----------")
bfs = test_graph.bfs()
for node in bfs:
    print(node.__dict__, node.op.__dict__)

print("\n-----------comprose----------")
composed_graph = test_graph.compose()
print(composed_graph)