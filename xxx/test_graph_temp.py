
# import pyximport
# pyximport.install()
# from graph import DirectedGraph

# graph = DirectedGraph()
# print(graph.__len__())

import logging
from collections import deque

import sys, os
path2add = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir, 'compat')))
print(sys.path)
print(path2add)
if (not (path2add in sys.path)) :
    sys.path.append(path2add)
from compat import six, Enum
