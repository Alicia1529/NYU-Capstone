    # @classmethod
    # def deserialize(cls, s_graph):
    #     from .tensor.core import ChunkData, TensorData

    #     graph = cls()
    #     node_type = TensorData if s_graph.level == SerialiableGraph.Level.TENSOR else ChunkData
    #     for node in s_graph.nodes:
    #         if isinstance(node, node_type):
    #             graph.add_node(node)
    #             if node.inputs:
    #                 for inode in node.inputs:
    #                     graph.add_node(inode)
    #                     graph.add_edge(inode, node)

    #     return graph