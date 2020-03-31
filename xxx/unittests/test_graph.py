
print("xxx/unittests/test_graph.py")

import os
import sys
path = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir)))

if (not (path in sys.path)) :
    sys.path.append(path)


from graph import DirectedGraph
test_graph = DirectedGraph()

# test DirectedGraph.add_node
node1 = {"key": 1, "op": "dot1", "inputs": ["3x4", "4x5"], "outputs":["3x5"] }
test_graph.add_node(1, node1)
node2 = {"key": 2, "op": "dot2", "inputs": ["1x2", "2x1"], "outputs":["1x1"] }
test_graph.add_node(2, node2)
node3 = {"key": 3, "op": "dot3", "inputs": ["1x9", "9x2"], "outputs":["1x2"] }
test_graph.add_node(3, node3)
node4 = {"key": 4, "op": "add", "inputs": ["3x4", "4"], "outputs":["3x4"] }
test_graph.add_node(4, node4)

# test DirectedGraph.add_edge
test_graph.add_edge(1, 2, {"edge":"1 -> 2"})
test_graph.add_edge(2, 3, {"edge":"2 -> 3"})
test_graph.add_edge(1, 4, {"edge":"1 -> 4"})

print(test_graph.get_nodes())
print(test_graph.iter_nodes())
to_dot = test_graph.to_dot()
# print(to_dot)

# graph = DirectedGraph()




# print(os.path.dirname())
# print(sys.path)
# print(__package__)
# print(__name__)
# print(__file__)
# print(os.path.dirname(__file__))
