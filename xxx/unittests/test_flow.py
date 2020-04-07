
print("xxx/unittests/test_flow.py")

import os
import sys
path = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir)))

if (not (path in sys.path)) :
    sys.path.append(path)

from operand import DataChunk, Operand
from graph import DirectedGraph

