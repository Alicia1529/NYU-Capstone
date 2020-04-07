import sys, os
path2add = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__))))

if (not (path2add in sys.path)) :
    sys.path.append(path2add)

from operators import op_dict
from operand import DataChunk, Operand
from graph import DirectedGraph
import weakref
from numpy import isscalar
import time
from copy import deepcopy


class OpArgMngr(object):
    """Operator argument manager for storing operator workloads."""
    graph = DirectedGraph()
    ops = {}

    @staticmethod
    def add_workload(funcname, *args, **kwargs):
        key = funcname + "." + str(int(time.time()))
        OpArgMngr.ops[key] = {'args': args, 'kwargs': kwargs, 'funcname': funcname}

    def add_assignment(variable, assigned_value):
