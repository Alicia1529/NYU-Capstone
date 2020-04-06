To use this to build your Cython file use the commandline options:

```
$ python setup.py build_ext --inplace
```

to-do list:
1. add all available operators to `xxx/operators.py`
2. test all operators in `xxx/unittests/test_operand.py`
3. data flows through operands
4. graph can work properly

Completed:

2020.4.2
1. add basic operators (Alicia)
2. program the basic operand logic and its execution (Alicia)
3. add a few test cases to `test_graph.py` and `test_operand.py` (Alicia)

2020.4.5
1. added more operators (Anqi)
2. modified operand logic and did tests (Anqi)

Current operand logic:

operand:
- id: str
- name: str
- inputs: list of `DataChunk`
- outputs: list of `DataChunk`

DataChunk:
- id: str
- data: dictionary if input, number if output