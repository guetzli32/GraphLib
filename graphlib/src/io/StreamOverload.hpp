#ifndef GL_STREAM_OVERLOAD_HPP
#define GL_STREAM_OVERLOAD_HPP

#include "../structures/Graph.hpp"
#include "../structures/Color.hpp"

/**
 * Prints various properties of the graph:
 *  - Number of nodes
 *  - Number of edges
 *  - Direction, Storage format
 *  - All edges
 * @name Graph output to stream 
 * @param os Stream that will be used for output
 * @param[in] rhs Graph that will be printed
 */
//@{
/**  
 * @brief Prints all info of a directed graph.
 */
template <class SCALAR, class STORAGE>
std::ostream& operator<< (std::ostream& os, const gl::Graph<SCALAR, STORAGE, gl::Directed>& rhs) {
  using idx_t = typename gl::Graph<SCALAR, STORAGE, gl::Directed>::idx_t;
  os << "----- " << rhs.getGraphLabel() << " -----" << std::endl
     << "Total Nodes: " << rhs.numNodes() << std::endl
     << "Total Edges: " << rhs.numEdges() << std::endl
     << "Directed " 
     << (GL_IS_MATRIX ? "Matrix" : (GL_IS_LIST ? "List" : "Unknown storage type"))
     << std::endl;
  for (auto it = rhs.edge_cbegin(); it != rhs.edge_cend(); ++it) {
    os << it->source() << "--(" << it->weight() 
        << ")->" << it->dest() << std::endl;
  }
  std::cout << std::endl;
  return os;
}

/** 
 * @brief Prints all info of an undirected graph.
 */
template <class SCALAR, class STORAGE>
std::ostream& operator<< (std::ostream& os, const gl::Graph<SCALAR, STORAGE, gl::Undirected>& rhs) {
  using idx_t = typename gl::Graph<SCALAR, STORAGE, gl::Undirected>::idx_t;
  os << "----- " << rhs.getGraphLabel() << " -----" << std::endl
     << "Total Nodes: " << rhs.numNodes() << std::endl
     << "Total Edges: " << rhs.numEdges() << std::endl
     << "Undirected " 
     << (GL_IS_MATRIX ? "Matrix" : (GL_IS_LIST ? "List" : "Unknown storage type"))
     << std::endl;
  for (auto it = rhs.edge_cbegin(); it != rhs.edge_cend(); ++it) {
    if (it->source() <= it->dest()) {
        os << it->source() << "<-(" << it->weight() 
           << ")->" << it->dest() << std::endl;
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
 * @param[in] rhs Container that will be printed
 */
//@{
/**
 * @brief Prints the value of a gl::Distance.
 */
template <class val_t>
std::ostream& operator<< (std::ostream& os, const gl::Distance<val_t>& dist)
{
  os << dist.getDistance();
  return os;
}


/**
 * @brief Prints all elements of an std::list.
 */
template <class idx_t>
std::ostream& operator<< (std::ostream & os, const std::list<idx_t>& rhs)
{
  os << "[ ";
  for (const auto& it : rhs) {
    os << it << " ";
  }
  os << "]\n";
  return os;
}

/**
 * @brief Prints all elements of an std::vector.
 */
template <class idx_t>
std::ostream& operator<< (std::ostream& os, const std::vector<idx_t>& rhs) {
  os << "[ ";
  for (const auto& it : rhs) {
    os << it << " ";
  }
  os << "]\n";
  return os;
}

/**
 * @brief Prints all elements of an std::deque.
 */
template <class idx_t>
std::ostream& operator<< (std::ostream& os, const std::deque<idx_t>& rhs) 
{
  os << "[ ";
  for (const auto& it : rhs) {
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
std::ostream& operator<< (std::ostream& os, std::stack<idx_t> rhs) 
{
  os << "[ ";
  while (!rhs.empty()) { 
    os << rhs.top() << " "; 
    rhs.pop(); 
  } 

  os << "]\n";
  return os;
}
//@}

/**
 * @brief Prints a gl::Color element. Format: [Hex code;(R,G,B),Opacity]
 * @param os Stream that will be used for output
 * @param[in] rhs Color that will be printed
 */
std::ostream& operator<< (std::ostream& os, const gl::Color& rhs) 
{
  os << "[Hex: #" << std::setw(8) << std::right 
     << std::hex << +rhs.hex() << std::setfill('0'); 
  os << ";(RGB: " << std::dec 
     << +rhs.r() << ","
     << +rhs.g() << "," 
     << +rhs.b() << "), Opacity: " 
     << +rhs.a() << "%]";
  return os;
}
/**
 * @brief Prints a gl::Edge element. Format: [Source-(Weight)->Destination;Weight/Capacity; Color]
 * @param os Stream that will be used for output
 * @param[in] rhs Edge that will be printed
 */
template<class SCALAR>
std::ostream& operator<< (std::ostream& os, const gl::Edge<SCALAR>& rhs) 
{
  os << "[" <<rhs.source() 
     << "--(" << rhs.weight() 
     << ")->" << rhs.dest() 
     << "; #" << rhs.color().RGBA() 
     << "]";
  return os;
}

#endif // GL_STREAM_OVERLOAD_HPP