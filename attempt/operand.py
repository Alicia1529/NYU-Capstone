#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright 1999-2018 Alibaba Group Holding Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import sys, os
path2add = os.path.normpath(os.path.abspath(os.path.join(os.path.dirname(__file__))))

if (not (path2add in sys.path)) :
    sys.path.append(path2add)

from operators import op_dict
import weakref
from numpy import isscalar
import time
from copy import deepcopy

# Data state: (waiting ->) ready


class DataChunk(object):
    # check data ?
    def __init__(self, data):
        self._id = None
        self._data = None
        if data is not None:
            self._set_data(data)

    @property
    def key(self):
        return self._id

    @property
    def data(self):
        return self._data
    
    @data.setter
    def data(self, new_data):
        self._set_data(new_data)

    def _set_data(self, new_data):
        self._data = new_data
        self._id = str(hash(time.time()))

    def isNumerical(self):
        return isscalar(self._data)

    def __copy__(self):
        return self.copy()

    def copy(self):
        self.copy_to(type(self)(None))

    def copy_to(self, target):
        target.data = self._data

    # def copy_from(self, obj):
    #     self.data = obj.data

# class Field:
#     def __init__(self, )

# operand state: waiting -> unscheduled -> ready -> running -> finished

class Operand:
    """
    Operand base class. All operands should have a type, which can be Add, Subtract etc.
    Operand can have inputs and outputs
    which should be the :class:`mars.tensor.core.TensorData`, :class:`mars.tensor.core.ChunkData` etc.
    """

    def __init__(self, op_name):
        self._op_id = self.hash_op_id(op_name)
        self._op_name = op_name
        self._inputs = dict()
        self._outputs = DataChunk(None)

    def hash_op_id(self, op_name):
        return str(hash(op_name))[:10] + "." + str(int(time.time()))

    @property
    def key(self):
        return self._op_id

    @property
    def op_name(self):
        return self._op_name

    @property
    def inputs(self):
        return self._inputs

    @inputs.setter
    def inputs(self, vals):
        self._set_inputs(vals)

    @property
    def outputs(self):
        return self._outputs

    @outputs.setter
    def outputs(self, outputs):
        self._set_outputs(outputs)

    def _set_inputs(self, inputs):
        self._inputs = inputs

    def _set_outputs(self, outputs):
        self._outputs = outputs
    
    def _get_input_data(self):
        output = deepcopy(self.inputs)
        for key in output:
            output[key] = output[key].data
        return output

    def execute(self):
        op = op_dict[self._op_name]
        output_chunk = DataChunk(None)
        output_chunk.data = op(**self._get_input_data())
        self.outputs = output_chunk
        return self.outputs
