#ifndef GL_DFS_HPP
#define GL_DFS_HPP

#include "../structures/Graph.hpp"

namespace gl {
namespace algorithm {

  /**
   * @brief Recursive call for DFS
   * @param graph The graph to run the algorithm on
   * @param node Start point of the graph search
   * @param visited list keeping track of already visited nodes
   * @param out result list
   */
  template <class GRAPH>
  void DFS_recursive (const GRAPH& graph, const typename GRAPH::idx_t node, typename GRAPH::visit_list_t& visited, typename GRAPH::ordered_list_t& out) {
    graph.checkRange(node);
    typename GRAPH::idx_list_t tempList; // temporary node lists
    typename GRAPH::DFS_queue_t queue; // nodes to check the neighbours of

    visited[node] = true;
    out.emplace_back(node);
    tempList = graph.getUnvisitedNeighbours(node,visited);
    
    for (auto v : tempList) {
      if (!visited[v]) {
        DFS_recursive(graph, v, visited, out);
      }
    }
  }

  /**
   * @brief Traverses the connected component of node using DFS
   * @param graph The graph to run the algorithm on
   * @param node Start point of the graph search
   * @tparam Graph Type of graph
   * @return Sequence of all nodes visited by a DFS run.
   */
  template <class Graph>
  typename Graph::ordered_list_t DFS (const Graph& graph, const typename Graph::idx_t node) {
    typename Graph::visit_list_t visited(graph.numNodes(),false);  // list of visited nodes
    typename Graph::ordered_list_t out;      // result node lists
    graph.checkRange(node);
    DFS_recursive(graph, node, visited, out);
    return out;
  }

} // namespace algorithm
} // namespace gl

#endif // GL_DFS_HPP