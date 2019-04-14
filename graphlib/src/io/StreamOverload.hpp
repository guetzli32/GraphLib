#ifndef GL_STREAM_OVERLOAD_HPP
#define GL_STREAM_OVERLOAD_HPP

#include "../structures/Graph.hpp"

/**
 * @name Graph output to stream 
 * Prints various properties of the graph:
 *  - Number of nodes
 *  - Number of edges
 *  - All edges
 *  - Direction, Storage format
 * /
//@{
/**  
 * @brief Prints all info of a directed graph.
 */
template <class SCALAR, class STORAGE_KIND>
std::ostream& operator<< (std::ostream& os, const gl::Graph<SCALAR, STORAGE_KIND, gl::Directed>& rhs) {
  using idx_t = typename gl::Graph<SCALAR, STORAGE_KIND, gl::Directed>::idx_t;
  os << "----- " << rhs.name() << " -----" << std::endl;
  os << "Total Nodes: " << rhs.numNodes() << std::endl;
  os << "Total Edges: " << rhs.numEdges() << std::endl;
  os << "Directed" << std::endl;
  for(idx_t start = 0; start < rhs.numNodes(); start++)
  {
    auto neighbours = rhs.getNeighbourWeights(start);
    for(const auto& edge : neighbours)
    {
      os << start << "--(" << edge.second << ")->" << edge.first << std::endl;
    }
  }
  std::cout << std::endl;
  return os;
}

/** 
 * @brief Prints all info of an undirected graph.
 */
template <class SCALAR, class STORAGE_KIND>
std::ostream& operator<< (std::ostream& os, const gl::Graph<SCALAR, STORAGE_KIND, gl::Undirected>& rhs) {
  using idx_t = typename gl::Graph<SCALAR, STORAGE_KIND, gl::Undirected>::idx_t;
  os << "----- " << rhs.name() << " -----" << std::endl;
  os << "Total Nodes: " << rhs.numNodes() << std::endl;
  os << "Total Edges: " << rhs.numEdges() << std::endl;
  os << "Undirected" << std::endl;
  for(idx_t start = 0; start < rhs.numNodes(); start++)
  {
    auto neighbours = rhs.getNeighbourWeights(start);
    for(const auto& edge : neighbours)
    {
      if (start < edge.first) {
        os << start << "<-(" << edge.second << ")->" << edge.first << std::endl;
      }
    }
  }
  std::cout << std::endl;
  return os;
}
//@}

/**
 * Prints all contents of the given GraphLib container.
 * @name Container output to stream
 * @param os Stream that will be used for output
 * @param rhs Container that will be printed
 */
//@{
/**
 * @brief Prints all elements of an std::list.
 */
template <class idx_t>
std::ostream& operator<< (std::ostream & os, const std::list<idx_t>& rhs) {
  os << "[ ";
  for (auto it : rhs)
    os << it << " ";
  os << "]\n";
  return os;
}

/**
 * @brief Prints all elements of an std::vector.
 */
template <class idx_t>
std::ostream& operator<< (std::ostream & os, const std::vector<idx_t>& rhs) {
  os << "[ ";
  for (auto it : rhs)
    os << it << " ";
  os << "]\n";
  return os;
}

/**
 * @brief Prints all elements of an std::deque.
 */
template <class idx_t>
std::ostream& operator<< (std::ostream & os, const std::deque<idx_t>& rhs) {
  os << "[ ";
  for (auto it : rhs) {
    os << it << " ";
  }

  os << "]\n";
  return os;
}

/**
 * Only supports copying the stack, due to its implementation.
 * @brief Prints all elements of an std::stack.
 */
template <class idx_t>
std::ostream& operator<< (std::ostream & os, std::stack<idx_t> rhs) {
  os << "[ ";
  while (!rhs.empty()) { 
    os << rhs.top() << " "; 
    rhs.pop(); 
  } 

  os << "]\n";
  return os;
}
//@}

#endif /* GL_STREAM_OVERLOAD_HPP */