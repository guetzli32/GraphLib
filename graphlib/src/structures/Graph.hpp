#ifndef GL_GRAPH_HPP
#define GL_GRAPH_HPP

#include <fstream>
#include <iostream>
#include <algorithm>
#include <exception>
#include <type_traits>
#include <cstdint>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <stack>
#include <iterator>

#include "Color.hpp"

namespace gl
{

class Matrix;
class List;

class Directed;
class Undirected;

///////////////////////////////////////////////////////////
//    Graph Class declaration
///////////////////////////////////////////////////////////

/** 
 * This class has functions to create and edit the graph, as well as access certain properties of the graph. 
 * @class Graph
 * @brief Stores and implements a Graph.
 * @tparam SCALAR Number type used to store edge weights.
 * @tparam STORAGE_KIND Class type used to signify that a matrix shall be stored in either Adjacency Matrix or Adjacency List format. Accepted Values: gl::Matrix, gl::List 
 * @tparam DIRECTION Class type used to signify that the graph is either directed or undirected. Accepted Values: gl::Directed, gl::Undirected 
 */

template <class SCALAR = int, class STORAGE_KIND = gl::List, class DIRECTION = gl::Undirected>
class Graph
{

public:
  using val_t = SCALAR;                                    ///< Value type
  using idx_t = std::size_t;                               ///< Index type
  using dest_vec_t = std::vector<std::pair<idx_t, val_t>>; ///< Destination-Vector type
  using idx_list_t = std::vector<idx_t>;                   ///< Index List type
  using ordered_list_t = std::list<idx_t>;                 ///< Ordered List type
  using visit_list_t = std::vector<bool>;                  ///< Visited-List type
  using BFS_queue_t = std::queue<idx_t>;                   ///< BFS type
  using DFS_queue_t = std::stack<idx_t>;                   ///< DFS type

  /** 
   * @class Edge
   * @brief Represents an Edge in a Graph.
   * @tparam SCALAR Number type used to store edge weights.
   * @tparam STORAGE_KIND Class type used to signify that a matrix shall be stored in either Adjacency Matrix or Adjacency List format. Accepted Values: gl::Matrix, gl::List 
   * @tparam DIRECTION Class type used to signify that the graph is either directed or undirected. Accepted Values: gl::Directed, gl::Undirected 
   */
  class Edge
  {
  public:
    /**
     * @brief Construct Edge from data
     * @param src Source index
     * @param dest Destination index
     * @param weight The weight of the %Edge
     * @param color Color of the %Edge
     * @param exists Whether the %Edge exists
     */
    Edge(const idx_t &src = 0, const idx_t &dest = 0, const val_t &weight = 0, const Color &color = Color(), const bool &exists = false) : src_(src), dest_(dest), weight_(weight), exists_(exists), color_(color) {}

    /**
     * @name exists
     * @brief Access to boolean value exists.
     * This signifies the existance of an edge in the graph.
     */
    //@{
    /**
     * @brief Checks whether an edge exists.
     * @return True if exists, false otherwise.
     */
    inline bool exists() const;
    /**
     * @brief Allows changing of existance status of an edge.
     * @param[in] exists New value of boolean exists.
     */
    inline void exists(bool exists);
    //@}
    /**
     * @name source
     * @brief Access to index of source node.
     */
    //@{
    /**
     * @brief Gets the index of the source of the edge.
     * @return index of edge source node.
     */
    inline idx_t source() const;
    /**
     * @brief Allows changing the source of an edge.
     * @param[in] src New value of source index.
     */
    inline void source(idx_t src);
    //@}
    /**
     * @name dest
     * @brief Access to index of destination node.
     */
    //@{
    /**
     * @brief Gets the index of the destination of the edge.
     * @return index of edge destination node.
     */
    inline idx_t dest() const;
    /**
     * @brief Allows changing the destination of an edge.
     * @param[in] dest New value of destination index.
     */
    inline void dest(idx_t dest);
    //@}
    /**
     * @name weight
     * @brief Access to weight of the edge.
     */
    //@{
    /**
     * @brief Gets the weight of the edge.
     * @return Weight of the edge.
     */
    inline val_t weight() const;
    /**
     * @brief Allows changing the weight of an edge.
     * @param[in] weight New value of edge weight.
     */
    inline void weight(val_t weight);
    /**
     * @name color
     * @brief Access to the edge's RGBA color value.
     */
    //@{
    /**
     * @brief Gets the edge's color.
     * @return Color of the edge.
     */
    inline Color color() const;
    /**
     * @brief Allows changing the edge's RGBA color value.
     * @param[in] color New color object. 
     */
    inline void color(const Color &color);
    //@}

  private:
    idx_t src_;    /**< @brief Source index */
    idx_t dest_;   /**< @brief Destination index */
    val_t weight_; /**< @brief Edge weight */
    bool exists_;  /**< @brief Edge existance */
    Color color_;  /**< @brief Edge color */
  };

  /** 
   * @class Node
   * @brief Represents a Node in a Graph.
   * @tparam SCALAR Number type used to store node capacities.
   * @tparam STORAGE_KIND Class type used to signify that a matrix shall be stored in either Adjacency Matrix or Adjacency List format. Accepted Values: gl::Matrix, gl::List 
   * @tparam DIRECTION Class type used to signify that the graph is either directed or undirected. Accepted Values: gl::Directed, gl::Undirected 
   */
  class Node
  {

  public:
    Node(const idx_t& id = 0, const val_t& capacity = 1, const std::string& label = "") : id_(id), label_(label), capacity_(capacity),
                                                                        inDegree_(0), outDegree_(0) {}

    /**
     * @name id
     * @brief Access to node ID.
     */
    //@{
    /**
     * @brief Checks whether an edge exists.
     * @return True if exists, false otherwise.
     */
    inline idx_t id() const;
    /**
     * @brief Allows changing of node ID.
     * @param id New value of node ID.
     */
    inline void id(const idx_t& id);
    //@}
    /**
     * @name name
     * @brief Access to the name of a node.
     */
    //@{
    /**
     * @brief Gets the label of a node.
     * @return label of the node.
     */
    inline std::string label() const;
    /**
     * @brief Allows changing the lable of a node.
     * @param name New value of node label.
     */
    inline void label(const std::string &name);
    //@}
    /**
     * @name capacity
     * @brief Access to capacity of the edge.
     */
    //@{
    /**
     * @brief Gets the capacity of the node.
     * @return Capacity of the node.
     */
    inline val_t capacity() const;
    /**
     * @brief Allows changing the capacity of a node.
     * @param capacity New value of node capacity.
     */
    inline void capacity(const val_t& capacity);
    //@}
    /**
     * @name color
     * @brief Access to the edge's RGBA color value.
     */
    //@{
    /**
     * @brief Gets the edge's color.
     * @return Color of the edge.
     */
    inline Color color() const;
    /**
     * @brief Allows changing the edge's RGBA color value.
     * @param[in] color New color object. 
     */
    inline void color(const Color &color);
    //@}
    /**
     * @name inDegree
     * @brief Access to node in-degree.
     */
    //@{
    /**
     * @brief Gets the in-degree of a node.
     * @return In-degree of a node.
     */
    inline idx_t inDegree() const;
    /**
     * @brief Increments the node in-degree.
     * @param[in] increment number that will be added
     */
    inline void inDegreeIncrement(const idx_t& increment = 1);
    /**
     * @brief Decrements the node in-degree.
     * @param[in] decrement number that will be subtracted
     */
    inline void inDegreeDecrement(const idx_t& decrement = 1);
    //@}
    /**
     * @name outDegree
     * @brief Access to node out-degree.
     */
    //@{
    /**
     * @brief Gets the out-degree of a node.
     * @return Out-degree of a node.
     */
    inline idx_t outDegree() const;
    /**
     * @brief Increments the node out-degree.
     * @param[in] increment number that will be added
     */
    inline void outDegreeIncrement(const idx_t& increment = 1);
    /**
     * @brief Decrements the node out-degree.
     * @param[in] decrement number that will be subtracted
     */
    inline void outDegreeDecrement(const idx_t& decrement = 1);
    //@}

  private:
    idx_t id_;         /**< @brief Node ID */
    std::string label_; /**< @brief Node label */
    val_t capacity_;   /**< @brief Node capacity */
    Color color_;      /**< @brief Node color */
    idx_t inDegree_;   /**< @brief In-degree */
    idx_t outDegree_;  /**< @brief Out-degree */
  };

  /** 
   * @class Property
   * @brief Stores the properties of a Graph.
   * @tparam SCALAR Number type used to store edge weights.
   * @tparam STORAGE_KIND Class type used to signify that a matrix shall be stored in either Adjacency Matrix or Adjacency List format. Accepted Values: gl::Matrix, gl::List 
   * @tparam DIRECTION Class type used to signify that the graph is either directed or undirected. Accepted Values: gl::Directed, gl::Undirected 
   */
  class Property
  {
  public:
    Property(const idx_t &numNodes, const std::string &name = "Graph", const idx_t &numEdges = 0) : numNodes_(numNodes), name_(name), numEdges_(0) {}
    Property(const Property &property) : numNodes_(property.numNodes_), name_(property.name_), numEdges_(property.numEdges_) {}

    /**
     * @name numNodes
     * @brief Access to the number of nodes in the graph.
     */
    //@{
    /**
     * @brief Gets the number of nodes in the graph.
     * @return Number of nodes in the graph.
     */
    inline idx_t numNodes() const;
    /**
     * @brief Allows changing the number of nodes in the graph.
     * @param numNodes New value of node count.
     */
    inline void numNodes(const idx_t &numNodes);
    /**
     * @brief Increments the number of nodes in the graph.
     * @param increment Number of nodes that will be added to the graph.
     */
    inline void numNodesIncrement(const idx_t &increment = 1);
    /**
     * @brief Decrements the number of nodes in the graph.
     * @param decrement Number of nodes that will be removed from the graph.
     */
    inline void numNodesDecrement(const idx_t &decrement = 1);
    //@}
    /**
     * @name numEdges
     * @brief Access to the number of edges in the graph.
     */
    //@{
    /**
     * @brief Gets the number of edges in the graph.
     * @return Number of edges in the graph.
     */
    inline idx_t numEdges() const;
    /**
     * @brief Allows changing the number of edges in the graph.
     * @param numEdges New value of edge count.
     */
    inline void numEdges(const idx_t &numEdges);
    /**
     * @brief Increments the number of edges in the graph.
     * @param increment Number of nodes that will be added to the graph.
     */
    inline void numEdgesIncrement(const idx_t &increment = 1);
    /**
     * @brief Decrements the number of edges in the graph.
     * @param decrement Number of edges that will be removed from the graph.
     */
    inline void numEdgesDecrement(const idx_t &decrement = 1);
    //@}
    /**
     * @name name
     * @brief Access to name of the graph.
     */
    //@{
    /**
     * @brief Gets the name of the graph.
     * @return Graph name.
     */
    inline std::string name() const;
    /**
     * @brief Allows changing the name of the graph.
     * @param name New graph name.
     */
    inline void name(const std::string &name);
    //@}

  private:
    idx_t numNodes_;   /**< @brief Number of nodes in the graph */
    idx_t numEdges_;   /**< @brief Number of edges in the graph */
    std::string name_; /**< @brief Name of the graph */
  };

  using matrix_t = std::vector<Edge>;         ///< Matrix Representation type
  using nodeList_t = std::list<Edge>;         ///< ListNode Representation type
  using rootList_t = std::vector<nodeList_t>; ///< ListRoot Representation type
  using NodeIterator = typename std::vector<Node>::iterator; ///< Node iterator type
  using ConstNodeIterator = typename std::vector<Node>::const_iterator; ///< Node const_iterator type

protected:
  Property property_; /**< @brief Stores various properties of the Graph. */

  std::vector<Node> nodes_;                                                                   /**< @brief Stores information about all nodes in the Graph. */
  std::conditional_t<std::is_same_v<STORAGE_KIND, Matrix>, matrix_t, rootList_t> edges_; /**< @brief Stores information about all edges in the Graph. */

public:
  /**
   * @name Construction
   * Various functions to create/destroy a Graph.
   */
  //@{
  /**
   * @brief Construct Graph from node count and name
   * @param numNodes Number of nodes/vertices in the graph.
   * @param name Name of the graph.
   */
  Graph(const idx_t &numNodes, const std::string &name = "Graph") : property_(numNodes, name, 0)
  {
    construct();
    std::vector<Node> nodes();
    for (idx_t i = 0; i < numNodes; ++i)
    {
      nodes_.push_back(Node(i));
    }
  }
  /**
   * @brief Construct Graph from property
   * @param property Properties for a graph.
   */
  Graph(const Property &property) : property_(property)
  {
    construct();
    std::vector<Node> nodes();
    for (idx_t i = 0; i < numNodes; ++i)
    {
      nodes_.push_back(Node(i));
    }
  }
  ~Graph()
  {
  }

///////////////////////////////////////////////////////////
//    Specialized function implementations
///////////////////////////////////////////////////////////

  /**
   * @brief Outputs a graph in Adjacency Matrix storage format with the same edges as this.
   * This function only exists for ListGraphs.
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST_DIRECTED
#endif
  gl::Graph<SCALAR, gl::Matrix, DIRECTION> toMatrix() const
  {
    gl::Graph<SCALAR, gl::Matrix, DIRECTION> out(numNodes(), getName());
    for (idx_t start = 0; start < edges_.size(); ++start)
    {
      for (auto &end : edges_[start])
      {
        out.setEdge(start, end.dest(), end.weight(), end.color());
      }
    }
    return out;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Converts an undirected ListGraph to an undirected MatrixGraph.
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  gl::Graph<SCALAR, gl::Matrix, DIRECTION> toMatrix() const
  {
    gl::Graph<SCALAR, gl::Matrix, DIRECTION> out(numNodes(), getName());
    for (idx_t start = 0; start < edges_.size(); ++start)
    {
      for (auto &end : edges_[start])
      {
        if(!out.hasEdge(start,end.dest()))
          out.setEdge(start, end.dest(), end.weight(), end.color());
      }
    }
    return out;
  }
#endif

  /**
   * @brief Outputs a graph in Adjacency List storage format with the same edges as this.
   * This function only exists for MatrixGraphs
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_MATRIX_DIRECTED
#endif
  gl::Graph<SCALAR, gl::List, gl::Directed> toList() const
  {
    gl::Graph<SCALAR, List, Directed> out(numNodes(), getName());
    for (idx_t i = 0; i < numNodes(); ++i)
    {
      for (idx_t j = 0; j < numNodes(); ++j)
      {
        if (hasEdge(i, j))
        {
          out.setEdge(i, j, edges_[i * numNodes() + j].weight(), edges_[i * numNodes() + j].color());
        }
      }
    }
    return out;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Outputs a graph in Adjacency List storage format with the same edges as this.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  gl::Graph<SCALAR, gl::List, gl::Undirected> toList() const
  {
    gl::Graph<SCALAR, List, Undirected> out(numNodes(), getName());
    for (idx_t i = 0; i < numNodes(); ++i)
    {
      for (idx_t j = i; j < numNodes(); ++j)
      {
        if (hasEdge(i, j))
        {
          out.setEdge(i, j, edges_[i * numNodes() + j].weight(), edges_[i * numNodes() + j].color());
        }
      }
    }
    return out;
  }
#endif
  //@}
  /**
   * @name Property interface
   * Provides access to the properties of the Graph.
   */
  //@{
  /**
   * @brief Returns the name of the graph.
   * @return name of the graph
   */
  inline std::string getName() const
  {
    return property_.name();
  }
  /**
   * @brief Changes the name of the graph.
   * @return New name of the graph
   */
  inline void setName(const std::string& name)
  {
    property_.name(name);
  }
  /**
   * @brief Returns the number of nodes currently in the graph.
   * @return number of nodes in the graph
   */
  inline idx_t numNodes() const
  {
    return property_.numNodes();
  }

  /**
   * @brief Returns the number of edges currently in the graph.
   * @return number of edges in the graph
   */
  inline idx_t numEdges() const
  {
    return property_.numEdges();
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_UNDIRECTED
#endif
  /**
   * @brief Returns true if the graph is undirected, false if not.
   * @return true if the graph is undirected, false if not.
   */
  inline bool isDirected() const
  {
    return false;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Version for directed graphs.
   */
  GL_ENABLE_IF_DIRECTED
  inline bool isDirected() const
  {
    return true;
  }
#endif
  /**
   * A quick algorithm that finds cycles in a graph.
   * A cycle in a graph is defined by a back edge (self-loop or edge connecting to an ancestor of the tree given by DFS).
   * An acyclic graph is also known as a tree.
   * @brief Checks whether the given graph containes cycles.
   * @return true if cyclic, false if acyclic
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Checks whether the given directed graph containes cycles using an iterative DFS approach.
   * @return true if cyclic, false if acyclic
   */
  GL_ENABLE_IF_DIRECTED
#endif
  bool hasCycle() const
  {
    visit_list_t visited(numNodes(), false);
    idx_list_t neighbourList;

    for (idx_t i = 0; i < numNodes(); i++)
    {
      neighbourList = getNeighbours(i);
      for (auto neighbour : neighbourList)
      {
        if (visited[neighbour])
        {
          return true;
        }
        else
        {
          visited[neighbour] = true;
        }
      }
    }
    return false;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Checks whether the given undirected graph containes cycles using an iterative BFS approach.
   * @return true if cyclic, false if acyclic
   */
  GL_ENABLE_IF_UNDIRECTED
  bool hasCycle() const
  {
    idx_t v = 0;
    idx_t parent = 0;
    std::deque<std::pair<idx_t, idx_t> > queue;
    idx_list_t tempList;
    visit_list_t visited (numNodes(),false);
    queue.push_front(std::make_pair(v, parent));
    visited[v] = true;

    while (!queue.empty())
    {
      v = queue.front().first;
      parent = queue.front().second;
      queue.pop_front();

      tempList = getNeighbours(v);
      for (auto elem : tempList) 
      {
        if (!visited[elem])
        {
          queue.push_front(std::make_pair(elem, v));
          visited[elem] = true;
        }
        else if (elem != parent)
          return true;
      }
    }
    return false;
  }
#endif
  //@}
  /**
   * @name Edge interface
   * Provides access to the properties of the edges in a Graph.
   */
  //@{
  /**
   * @brief Sets an edge including start/end points and weight.
   * @param start edge origin point
   * @param end edge end point
   * @param weight new edge weight
   * @param color (Optional) new edge color
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST_DIRECTED
#endif
  void setEdge(const idx_t& start, const idx_t& end, const val_t& weight = 1, const Color& color = Color())
  {
    GL_ASSERT((!hasEdge(start, end)), std::string("There is already an edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));

    edges_[start].push_back(Edge(start, end, weight, color, true));
    property_.numEdgesIncrement();
    nodes_[start].outDegreeIncrement();
    nodes_[end].inDegreeIncrement();
  }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Adds edge in an Undirected List Graph.
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void setEdge(const idx_t& start, const idx_t& end, const val_t& weight = 1, const Color& color = Color())
  {
    GL_ASSERT((!hasEdge(start, end)), std::string("There is already an edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start].push_back(Edge(start, end, weight, color, true));
    property_.numEdgesIncrement();
    nodes_[start].outDegreeIncrement();
    nodes_[end].inDegreeIncrement();
    if(start != end) { // for avoiding double-adding self loops
      edges_[end].push_back(Edge(end, start, weight, color, true));
      nodes_[start].inDegreeIncrement();
      nodes_[end].outDegreeIncrement();
    }
  }

  /**
   * @brief Adds edge in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  void setEdge(const idx_t& start, const idx_t& end, const val_t& weight = 1, const Color& color = Color())
  {
    GL_ASSERT((!hasEdge(start, end)), std::string("There is already an edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start * numNodes() + end].weight(weight);
    edges_[start * numNodes() + end].exists(true);
    edges_[start * numNodes() + end].color(color);
    property_.numEdgesIncrement();
    nodes_[start].outDegreeIncrement();
    nodes_[end].inDegreeIncrement();
  }

  /**
   * @brief Adds edge in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  void setEdge(idx_t start, idx_t end, const val_t& weight = 1, const Color& color = {})
  {
    if (start > end)
      std::swap(end, start);
    GL_ASSERT((!hasEdge(start, end)), std::string("There is already an edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start * numNodes() + end].color(color);
    edges_[start * numNodes() + end].weight(weight);
    if (!hasEdge(start, end))
    {
      edges_[start * numNodes() + end].exists(true);
      property_.numEdgesIncrement();
      nodes_[start].inDegreeIncrement();
      nodes_[start].outDegreeIncrement();
      nodes_[end].inDegreeIncrement();
      nodes_[end].outDegreeIncrement();
    }
  }
#endif
  /**
   * @brief Adds edges in the format "<start> <end> <weight>" found in inFile to the graph.
   * @param inFile file name of input file
   */
  void addEdgesFromFile(const std::string& inFile)
  {
    std::ifstream is;
    is.open(inFile, std::ios::in);
    if (!is.is_open())
    {
      std::cout << "Error: failed to open " << inFile << '\n';
    }
    else
    {
      idx_t start;
      idx_t end;
      val_t weight;
      while (is >> start >> end >> weight)
      {
        setEdge(start, end, weight);
      }
    }
  }

  /**
   * @brief Updates edge properties. Parameters "start" & "end" mandatory, the rest optional.
   * @param[in] start Edge origin point
   * @param[in] end Edge end point
   * @param[in] weight (Optional) New edge weight
   * @param[in] color (Optional) New edge color
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Updates the weight & color of an edge from start to end.
   * @param[in] start Edge origin point
   * @param[in] end Edge end point
   * @param[in] weight New edge weight
   * @param[in] color New edge color
   */
  GL_ENABLE_IF_LIST_DIRECTED
#endif
  void updateEdge(const idx_t& start, const idx_t& end, const val_t& weight, const Color &color)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    (*it).color(color);
    (*it).weight(weight);
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Updates edge weight in a Directed List Graph.
   * @param[in] start Edge origin point
   * @param[in] end Edge end point
   * @param[in] weight New edge weight
   */
  GL_ENABLE_IF_LIST_DIRECTED
  void updateEdge(const idx_t& start, const idx_t& end, const val_t& weight)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    (*it).weight(weight);
  }
  /**
   * @brief Updates edge color in a Directed List Graph.
   * @param[in] start Edge origin point
   * @param[in] end Edge end point
   * @param[in] color New edge color
   */
  GL_ENABLE_IF_LIST_DIRECTED
  void updateEdge(const idx_t& start, const idx_t& end, const Color& color)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    (*it).color(color);
  }

  /**
   * @brief Updates edge weight & color in an Undirected List Graph.
   * @param[in] start Edge origin point
   * @param[in] end Edge end point
   * @param[in] weight New edge weight
   * @param[in] color New edge color
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void updateEdge(const idx_t& start, const idx_t& end, const val_t& weight, const Color& color)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    (*it).weight(weight);
    (*it).color(color);

    it = std::find_if(edges_[end].begin(), edges_[end].end(),
                      [&start](const Edge &node) { return node.dest() == start; });
    (*it).weight(weight);
    (*it).color(color);
  }
  /**
   * @brief Updates edge weight in an Undirected List Graph.
   * @param[in] start Edge origin point
   * @param[in] end Edge end point
   * @param[in] weight New edge weight
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void updateEdge(const idx_t& start, const idx_t& end, const val_t& weight)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    (*it).weight(weight);

    it = std::find_if(edges_[end].begin(), edges_[end].end(),
                      [&start](const Edge &node) { return node.dest() == start; });
    (*it).weight(weight);
  }
  /**
   * @brief Updates edge color in an Undirected List Graph.
   * @param[in] start Edge origin point
   * @param[in] end Edge end point
   * @param[in] color New edge color
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void updateEdge(const idx_t& start, const idx_t& end, const Color& color)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    (*it).color(color);

    it = std::find_if(edges_[end].begin(), edges_[end].end(),
                      [&start](const Edge &node) { return node.dest() == start; });
    (*it).color(color);
  }

  /**
   * @brief Updates edge weight & color in a Directed Matrix Graph.
   * @param[in] start Edge origin point
   * @param[in] end Edge end point
   * @param[in] weight New edge weight
   * @param[in] color New edge color
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline void updateEdge(const idx_t& start, const idx_t& end, const val_t& weight, const Color& color)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start * numNodes() + end].weight(weight);
    edges_[start * numNodes() + end].color(color);
  }
  /**
   * @brief Updates edge weight in a Directed Matrix Graph.
   * @param[in] start Edge origin point
   * @param[in] end Edge end point
   * @param[in] weight New edge weight
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline void updateEdge(const idx_t& start, const idx_t& end, const val_t& weight)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start * numNodes() + end].weight(weight);
  }
  /**
   * @brief Updates edge color in a Directed Matrix Graph.
   * @param[in] start Edge origin point
   * @param[in] end Edge end point
   * @param[in] color New edge color
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline void updateEdge(const idx_t& start, const idx_t& end, const Color& color)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start * numNodes() + end].color(color);
  }

  /**
   * @brief Updates edge weight & color in an Undirected Matrix Graph.
   * @param[in] start Edge origin point
   * @param[in] end Edge end point
   * @param[in] weight New edge weight
   * @param[in] color New edge color
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline void updateEdge(idx_t start, idx_t end, const val_t& weight, const Color& color)
  {
    if (start > end)
      std::swap(end, start);
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start * numNodes() + end].weight(weight);
    edges_[start * numNodes() + end].color(color);
  }
  /**
   * @brief Updates edge weight in an Undirected Matrix Graph.
   * @param[in] start Edge origin point
   * @param[in] end Edge end point
   * @param[in] weight New edge weight
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline void updateEdge(idx_t start, idx_t end, const val_t& weight)
  {
    if (start > end)
      std::swap(end, start);
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start * numNodes() + end].weight(weight);
  }
  /**
   * @brief Updates edge color in an Undirected Matrix Graph.
   * @param[in] start Edge origin point
   * @param[in] end Edge end point
   * @param[in] color New edge color
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline void updateEdge(idx_t start, idx_t end, const Color& color)
  {
    if (start > end)
      std::swap(end, start);
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    edges_[start * numNodes() + end].color(color);
  }
#endif

  /**
   * @brief Deletes the edge going from start to end.
   * @param start edge origin point
   * @param end edge end point
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST_DIRECTED
#endif
  void delEdge(const idx_t& start, const idx_t& end)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    edges_[start].erase(it);
    property_.numEdgesDecrement();
    nodes_[start].outDegreeDecrement();
    nodes_[end].inDegreeDecrement();
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Deletes edge in an Undrected List Graph.
   */
  GL_ENABLE_IF_LIST_UNDIRECTED
  void delEdge(const idx_t& start, const idx_t& end)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    edges_[start].erase(it);
    it = std::find_if(edges_[end].begin(), edges_[end].end(),
                      [&start](const Edge &node) { return node.dest() == start; });
    edges_[end].erase(it);
    property_.numEdgesDecrement();
    nodes_[start].inDegreeDecrement();
    nodes_[start].outDegreeDecrement();
    nodes_[end].inDegreeDecrement();
    nodes_[end].outDegreeDecrement();
  }

  /**
   * @brief Deletes edge in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline void delEdge(const idx_t& start, const idx_t& end)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    checkRange(start, end);
    edges_[start * numNodes() + end].weight(SCALAR(0));
    edges_[start * numNodes() + end].exists(false);
    property_.numEdgesDecrement();
    nodes_[start].outDegreeDecrement();
    nodes_[end].inDegreeDecrement();
  }

  /**
   * @brief Deletes edge in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline void delEdge(idx_t start, idx_t end)
  {
    GL_ASSERT((hasEdge(start, end)), std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end));
    if (start > end)
      std::swap(end, start);
    edges_[start * numNodes() + end].weight(SCALAR(0));
    edges_[start * numNodes() + end].exists(false);
    property_.numEdgesDecrement();
    nodes_[start].inDegreeDecrement();
    nodes_[start].outDegreeDecrement();
    nodes_[end].inDegreeDecrement();
    nodes_[end].outDegreeDecrement();
  }
#endif

  /**
   * @brief Checks whether an edge exists from start to end.
   * @param start edge origin point
   * @param end edge end point
   * @return true if there exists an edge, false otherwise
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
#endif
  bool hasEdge(const idx_t& start, const idx_t& end) const
  {
    checkRange(start, end);
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    return it != edges_[start].end();
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Checks whether an edge exists in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline bool hasEdge(const idx_t& start, const idx_t& end) const
  {
    checkRange(start, end);
    return edges_[start * numNodes() + end].exists();
  }

  /**
   * @brief Checks whether an edge exists in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline bool hasEdge(idx_t start, idx_t end) const
  {
    checkRange(start, end);
    if (start > end)
      std::swap(end, start);
    return edges_[start * numNodes() + end].exists();
  }
#endif

  /**
   * @brief Finds the weight of the edge going from start to end.
   * @param start edge origin point
   * @param end edge end point
   * @return weight of the selected edge
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
#endif
  val_t getEdgeWeight(const idx_t& start, const idx_t& end) const
  {
    GL_ASSERT(hasEdge(start, end), (std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end)))
    auto it = std::find_if(edges_[start].begin(), edges_[start].end(),
                           [&end](const Edge &node) { return node.dest() == end; });
    return (*it).weight();
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Finds the weight of an edge in a Directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
  inline val_t getEdgeWeight(const idx_t& start, const idx_t& end) const
  {
    GL_ASSERT(hasEdge(start, end), (std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end)))
    return edges_[start * numNodes() + end].weight();
  }

  /**
   * @brief Finds the weight of an edge in an Undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  inline val_t getEdgeWeight(idx_t start, idx_t end) const
  {
    if (start > end)
      std::swap(end, start);
    GL_ASSERT(hasEdge(start, end), (std::string("No edge from ") + std::to_string(start) + std::string(" to ") + std::to_string(end)))
    return edges_[start * numNodes() + end].weight();
  }
#endif
  /**
   * @brief Returns the color of the edge from src to dest.
   * @param src edge origin point
   * @param dest edge destination point
   * @return Color of edge src->dest
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Gets the color of an edge in a directed Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_DIRECTED
#endif
  Color getEdgeColor(const idx_t& src, const idx_t& dest) const
  {
    return edges_[src * numNodes() + dest].color();
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Gets the color of an edge in an undirected Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX_UNDIRECTED
  Color getEdgeColor(idx_t src, idx_t dest) const
  {
    if (src > dest)
      std::swap(src, dest);
    return edges_[src * numNodes() + dest].color();
  }
  /**
   * @brief Gets the color of an edge in a List Graph.
   */
  GL_ENABLE_IF_LIST
  Color getEdgeColor(const idx_t& src, const idx_t& dest) const
  {
    auto it = std::find_if(edges_[src].begin(), edges_[src].end(),
                           [&dest](const Edge &node) { return node.dest() == dest; });
    return (*it).color();
  }
#endif  
  /**
   * @brief %EdgeIterator class.
   * Used to iterate over all Edges in the Graph
   */
  class EdgeIterator
  {
  public:
    using self_t = EdgeIterator;                         ///< EdgeIterator type
    using value_type = Edge;                                  ///< Edge type
    using reference = Edge&;                                ///< Edge reference type
    using pointer = Edge*;                            ///< Edge pointer type
    using iterator_category = std::forward_iterator_tag; ///< Iterator category
    using difference_type = std::ptrdiff_t;                       ///< Pointer Difference type
    /**
     * @brief Default constructor
     */
    EdgeIterator() {}
    /**
     * @brief Construct EdgeIterator, only used with Matrix Representation
     * @param ptr Pointer to which edge this iterator should point
     * @param data1 ?
     * @param data2 ?
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_MATRIX
#endif
    EdgeIterator(pointer ptr, pointer data1, idx_t data2) : ptr_(ptr), data1_(data1), data2_(data2)
    {
    }
    /**
     * @brief Construct EdgeIterator, only used with List Representation
     * @param ptr Pointer to which edge this iterator should point
     * @param data1 ?
     * @param data2 ?
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_LIST
#endif
    EdgeIterator(typename nodeList_t::iterator ptr, typename rootList_t::iterator data1, Graph<SCALAR, STORAGE_KIND, DIRECTION> *data2) : ptr_(ptr), data1_(data1), data2_(data2)
    {
    }

    /**
     * @brief Move Iterator to next edge (pre-increment)
     * @return new Iterator
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_MATRIX
#endif
    self_t operator++()
    {
      ++ptr_;
      while (ptr_ - data1_ < data2_ && !ptr_->exists())
      {
        ptr_++;
      }
      return *this;
    }
    /**
     * @brief Move Iterator to next edge (post-increment)
     * @return new Iterator
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_MATRIX
#endif
    self_t operator++(int dummy)
    {
      self_t i = *this;
      ptr_++;
      while (ptr_ - data1_ < data2_ && !ptr_->exists())
      {
        ptr_++;
      }
      return i;
    }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_LIST
    self_t operator++()
    {
      ++ptr_;
      if (ptr_ == data1_->end() && ((data1_ + 1) != data2_->edges_.end()))
      {
        ++data1_;
        while (data1_->size() == 0 && ((data1_ + 1) != data2_->edges_.end())) {
          ++data1_;
        }
        ptr_ = data1_->begin();
      }
      return *this;
    }
    GL_ENABLE_IF_LIST
    self_t operator++(int dummy)
    {
      self_t i = *this;
      ++ptr_;
      if (ptr_ == data1_->end() && ((data1_ + 1) != data2_->edges_.end()))
      {
        ++data1_;
        while (data1_->size() == 0 && ((data1_ + 1) != data2_->edges_.end())) {
          ++data1_;
        }
        ptr_ = data1_->begin();
      }
      return i;
    }
#endif
    /**
     * @brief Dereference iterator
     * @return A Reference to the underlying edge
     */
    value_type& operator*() { return *ptr_; }
    /**
     * @brief Get underlying edge
     * @return Pointer to underlying edge
     */
    value_type* operator->() { return &operator*(); }
    /**
     * @brief Check if equal
     * @return If both iterators are equal
     */
    bool operator==(const self_t &rhs) { return ptr_ == rhs.ptr_ && data1_ == rhs.data1_ && data2_ == rhs.data2_; }
    /**
     * @brief Check if not equal
     * @return If both iterators are not equal
     */
    bool operator!=(const self_t &rhs) { return !operator==(rhs); }

    /**
     * @brief Construct from Assignment
     * @return If both iterators are not equal
     */
    self_t operator=(const self_t &rhs)
    {
      ptr_ = rhs.ptr_;
      data1_ = rhs.data1_;
      data2_ = rhs.data2_;
    }

  private:
    std::conditional_t<std::is_same_v<STORAGE_KIND, Matrix>, pointer, typename nodeList_t::iterator> ptr_;          ///< @brief pointer that will be deferenced in Matrix, iterator over the nodeLists for List
    std::conditional_t<std::is_same_v<STORAGE_KIND, Matrix>, pointer, typename rootList_t::iterator> data1_;        ///< @brief pointer to first element for Matrix, iterator over the rootList for List
    std::conditional_t<std::is_same_v<STORAGE_KIND, Matrix>, idx_t, Graph<SCALAR, STORAGE_KIND, DIRECTION> *> data2_; ///< @brief size of adjacency matrix for matrix, pointer to this Graph for List
  };

  /**
   * @brief %ConstEdgeIterator class.
   * Used to iterate over all Edges in the Graph (and not write access)
   */
  class ConstEdgeIterator
  {
  public:
    using self_t = ConstEdgeIterator;                    ///< ConstEdgeIterator type
    using value_type = Edge;                                  ///< Edge type
    using reference = const Edge&;                                ///< Edge reference type
    using pointer = const Edge*;                            ///< Edge pointer type
    using iterator_category = std::forward_iterator_tag; ///< Iterator category
    using difference_type = std::ptrdiff_t;                       ///< Pointer Difference type
    /**
     * @brief Default Constructor
     */
    ConstEdgeIterator() {}

    /**
     * @brief Construct ConstEdgeIterator
     * @param ptr Pointer to which edge this iterator should point
     * @param data1 ?
     * @param data2 ?
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_MATRIX
#endif
    ConstEdgeIterator(pointer ptr, pointer data1, idx_t data2) : ptr_(ptr), data1_(data1), data2_(data2)
    {
    }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_LIST
#endif
    ConstEdgeIterator(typename nodeList_t::const_iterator ptr, typename rootList_t::const_iterator data1, const Graph<SCALAR, STORAGE_KIND, DIRECTION> *data2) : ptr_(ptr), data1_(data1), data2_(data2)
    {
    }

    /**
     * @brief Move Iterator to next edge (pre-increment)
     * @return new Iterator
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_MATRIX
#endif
    self_t operator++()
    {
      ++ptr_;
      while (ptr_ - data1_ < data2_ && !ptr_->exists())
      {
        ptr_++;
      }
      return *this;
    }
    /**
     * @brief Move Iterator to next edge (post-increment)
     * @return new Iterator
     */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_MATRIX
#endif
    self_t operator++(int dummy)
    {
      self_t i = *this;
      ptr_++;
      while (ptr_ - data1_ < data2_ && !ptr_->exists())
      {
        ptr_++;
      }
      return i;
    }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    GL_ENABLE_IF_LIST
    self_t operator++()
    {
      ++ptr_;
      if (ptr_ == data1_->end() && ((data1_ + 1) != data2_->edges_.end()))
      {
        ++data1_;
        while (data1_->size() == 0 && ((data1_ + 1) != data2_->edges_.end())) {
          ++data1_;
        }
        ptr_ = data1_->begin();
      }
      return *this;
    }
    GL_ENABLE_IF_LIST
    self_t operator++(int dummy)
    {
      self_t i = *this;
      ++ptr_;
      if (ptr_ == data1_->end() && ((data1_ + 1) != data2_->edges_.end()))
      {
        ++data1_;
        while (data1_->size() == 0 && ((data1_ + 1) != data2_->edges_.end())) {
          ++data1_;
        }
        ptr_ = data1_->begin();
      }
      return i;
    }
#endif
    /**
     * @brief Dereference iterator
     * @return A const Reference to the underlying edge
     */
    const value_type& operator*() { return *ptr_; }
    /**
     * @brief Get underlying edge
     * @return const Pointer to underlying edge
     */
    const value_type *operator->() { return &operator*(); }

    /**
     * @brief Assignment constructor
     * @return A new EdgeIterator
     */
    self_t operator=(const self_t &rhs)
    {
      ptr_ = rhs.ptr_;
      data1_ = rhs.data1_;
      data2_ = rhs.data2_;
    }
    /**
     * @brief Check if equal
     * @return If both iterators are equal
     */
    bool operator==(const self_t &rhs) { return ptr_ == rhs.ptr_ && data1_ == rhs.data1_ && data2_ == rhs.data2_; }
    /**
     * @brief Check if not equal
     * @return If both iterators are not equal
     */
    bool operator!=(const self_t &rhs) { return !operator==(rhs); }

  private:
    std::conditional_t<std::is_same_v<STORAGE_KIND, Matrix>, pointer, typename nodeList_t::const_iterator> ptr_;    //< @brief pointer that will be deferenced in Matrix, iterator over the nodeLists for List
    std::conditional_t<std::is_same_v<STORAGE_KIND, Matrix>, pointer, typename rootList_t::const_iterator> data1_;  //< @brief pointer to first element for Matrix, iterator over the rootList for List
    std::conditional_t<std::is_same_v<STORAGE_KIND, Matrix>, idx_t, const Graph<SCALAR, STORAGE_KIND, DIRECTION> *> data2_; //< @brief size of adjacency matrix for matrix, pointer to this Graph for List
  };
  /**
   * @brief EdgeIterator to the first edge
   * @return Iterator to the first edge
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_MATRIX
#endif
  EdgeIterator edge_begin()
  {
    Edge *ptr = &edges_.front();
    Edge *start = &edges_.front();
    idx_t end = numNodes() * numNodes();
    while (!ptr->exists())
    {
      ptr++;
    }
    return EdgeIterator(ptr, start, end);
  }
  /**
   * @brief EdgeIterator to behind the last edge
   * @return Iterator to behind the last edge
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_MATRIX
#endif
  EdgeIterator edge_end()
  {
    return EdgeIterator(&edges_.back() + 1, &edges_.front(), numNodes() * numNodes());
  }
  /**
   * @brief ConstEdgeIterator to the first edge
   * @return Iterator to the first edge
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_MATRIX
#endif
  ConstEdgeIterator edge_cbegin() const
  {
    auto ptr = &edges_.front();
    const auto start = &edges_.front();
    idx_t end = numNodes() * numNodes();
    while (!ptr->exists())
    {
      ptr++;
    }
    return ConstEdgeIterator(ptr, start, end);
  }
  /**
   * @brief ConstEdgeIterator to the last edge
   * @return Iterator to last edge
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_MATRIX
#endif
  ConstEdgeIterator edge_cend() const
  {
    return ConstEdgeIterator(&edges_.back() + 1, &edges_.front(), numNodes() * numNodes());
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
  EdgeIterator edge_begin()
  {
    auto it = edges_.begin();
    while (it->size() == 0)
      ++it;
    return EdgeIterator(edges_[it - edges_.begin()].begin(), it, this);
  }
  GL_ENABLE_IF_LIST
  EdgeIterator edge_end()
  {
    return EdgeIterator(edges_.back().end(), edges_.end() - 1, this);
  }

  GL_ENABLE_IF_LIST
  ConstEdgeIterator edge_cbegin() const
  {
    auto it = edges_.cbegin();
    while (it->size() == 0)
      ++it;
    return ConstEdgeIterator(edges_[it - edges_.begin()].cbegin(), it, this);
  }
  GL_ENABLE_IF_LIST
  ConstEdgeIterator edge_cend() const 
  {
    return ConstEdgeIterator(edges_.back().cend(), edges_.cend() - 1, this);
  }
#endif
  //@}
  /**
   * @name Node interface
   * Provides access to the properties of the nodes in the Graph.
   */
  //@{
  /**
   * @brief Returns a list of all endpoints of outgoing edges from start.
   * @param node edge origin point
   * @return List of all direct neighbours
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
#endif
  idx_list_t getNeighbours(const idx_t& node) const
  {
    idx_list_t out;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(node, end))
      {
        out.push_back(end);
      }
    }
    return out;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Gets a list of all node neighbours in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX
  idx_list_t getNeighbours(const idx_t& node) const
  {
    idx_list_t out;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(node, end))
        out.push_back(end);
    }
    return out;
  }
#endif

  /**
   * @brief Returns a list of endpoints + edge weights of outgoing edges from start.
   * @param node edge origin point
   * @param visited boolean list of previously visited nodes
   * @return List of all direct neighbours + weights
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
#endif
  idx_list_t getUnvisitedNeighbours(const idx_t& node, const std::vector<bool>& visited) const
  {
    idx_list_t out;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(node, end) && !visited[end])
        out.push_back(end);
    }
    return out;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Gets a list of unvisited node neighbours in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX
  idx_list_t getUnvisitedNeighbours(const idx_t& node, const std::vector<bool>& visited) const
  {
    idx_list_t out;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(node, end) && !visited[end])
        out.push_back(end);
    }
    return out;
  }
#endif

  /**
   * @brief Returns a list of endpoints + edge weights of outgoing edges from start.
   * @param node edge origin point
   * @return List of all direct neighbours + weights
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
#endif
  dest_vec_t getNeighbourWeights(const idx_t& node) const
  {
    dest_vec_t out;
    for (const auto &edge : edges_[node])
    {
      out.push_back(std::make_pair(edge.dest(), edge.weight()));
    }
    return out;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Gets list & weights of outgoing edges in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX
  dest_vec_t getNeighbourWeights(const idx_t& node) const
  {
    dest_vec_t out;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(node, end))
        out.push_back(std::make_pair(end, getEdgeWeight(node, end)));
    }
    return out;
  }
#endif
  /**
   * @brief Returns a list of endpoints + edge weights of unvisited outgoing edges from start.
   * @param node edge origin point
   * @param visited boolean list of previously visited nodes
   * @return List of all direct neighbours + weights
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
#endif
  dest_vec_t getUnvisitedNeighbourWeights(const idx_t& node, const visit_list_t& visited) const
  {
    dest_vec_t out;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(node, end) && !visited[end])
        out.push_back(std::make_pair(end, getEdgeWeight(node, end)));
    }
    return out;
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Gets a list of unvisited edges (weight + neighbour) in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX
  dest_vec_t getUnvisitedNeighbourWeights(const idx_t& node, const visit_list_t& visited) const
  {
    dest_vec_t out;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(node, end) && !visited[end])
        out.push_back(std::make_pair(end, getEdgeWeight(node, end)));
    }
    return out;
  }
#endif
  /**
   * @brief Updates node properties. Parameter "node" mandatory, the rest optional.
   * @param[in] id ID of the node that should be updated.
   * @param[in] label (Optional) New label for the node.
   * @param[in] capacity (Optional) New flow capacity for the node.
   * @param[in] color (Optional) New color for the node.
   */
  inline void updateNode(const idx_t& id, const std::string& label, const val_t& capacity, const Color& color) {
    updateNode(id,label);
    updateNode(id,capacity);
    updateNode(id,color);
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Updates node label & flow capacity.
   * @param[in] id ID of the node that should be updated.
   * @param[in] label New label for the node.
   * @param[in] capacity New flow capacity for the node.
   */
  inline void updateNode(const idx_t& id, const std::string& label, const val_t& capacity) {
    updateNode(id,label);
    updateNode(id,capacity);
  }
  /**
   * @brief Updates node flow capacity & color.
   * @param[in] id ID of the node that should be updated.
   * @param[in] capacity New flow capacity for the node.
   * @param[in] color New color for the node.
   */
  inline void updateNode(const idx_t& id, const val_t& capacity, const Color& color) {
    updateNode(id,capacity);
    updateNode(id,color);
  }
  /**
   * @brief Updates node custom name & color.
   * @param[in] od ID of the node that should be updated.
   * @param[in] label New label for the node.
   * @param[in] color New color for the node.
   */
  inline void updateNode(const idx_t& id, const std::string& label, const Color& color) {
    updateNode(id,label);
    updateNode(id,color);    
  }
  /**
   * @brief Updates node label.
   * @param[in] id ID of the node that should be updated.
   * @param[in] label New label for the node.
   */
  inline void updateNode(const idx_t& id, const std::string& label) {
    nodes_[id].label(label);
  }
  /**
   * @brief Updates node flow capacity.
   * @param[in] id ID of the node that should be updated.
   * @param[in] capacity New flow capacity for the node.
   */
  inline void updateNode(const idx_t& id, const val_t& capacity) {
    nodes_[id].capacity(capacity);
  }
  /**
   * @brief Updates node color.
   * @param[in] id ID of the node that should be updated.
   * @param[in] color New color for the node.
   */
  inline void updateNode(const idx_t& id, const Color& color) {
    nodes_[id].color(color);
  }
#endif

  /**
   * @brief Finds the label of the given node.
   * @param[in] id ID of the node whose lavel is to be found.
   * @return Label of node
   */
  inline std::string getNodeLabel(const idx_t& id) const
  {
    return nodes_[id].label();
  }
  /**
   * @brief Finds the flow capactiy of the given node.
   * @param[in] id node whose flow capacity is to be found
   * @return Capacity of node
   */
  inline val_t getNodeCapacity(const idx_t& id) const
  {
    return nodes_[id].capacity();
  }
  /**
   * @brief Finds the degree of the given node (i.e. count of all in- & outgoing edges).
   * @param id node whose degree is to be found
   * @return Degree of node
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  GL_ENABLE_IF_LIST
#endif
  inline idx_t getNodeDegree(const idx_t& id) const
  {
    return edges_[id].size();
  }
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Gets the degree of a node in a Matrix Graph.
   */
  GL_ENABLE_IF_MATRIX
  idx_t getNodeDegree(const idx_t& id) const
  {
    idx_t count = 0;
    for (idx_t end = 0; end < numNodes(); ++end)
    {
      if (hasEdge(id, end))
        ++count;
    }
    return count;
  }
#endif

  /**
   * @brief Gets the in-degree of a node (i.e. count of all incoming edges).
   */
  idx_t getNodeInDegree(const idx_t& id) const {
    return nodes_[id].inDegree();
  }
  /**
   * @brief Gets the in-degree of a node (i.e. count of all outgoing edges).
   */
  idx_t getNodeOutDegree(const idx_t& id) const {
    return nodes_[id].outDegree();
  }
  /**
   * @brief Returns the color of a node.
   * @param id Node ID
   * @return Color of node with ID "id".
   */
  Color getNodeColor(const idx_t& id) const
  {
    return nodes_[id].color();
  }
  /**
   * @brief NodeIterator to the first node
   * @return Iterator to first node
   */
  NodeIterator node_begin()
  {
    return NodeIterator(nodes_.begin());
  }
  /**
   * @brief NodeIterator to behind the last node
   * @return Iterator to behind the last node
   */
  NodeIterator node_end()
  {
    return NodeIterator(nodes_.end());
  }
  /**
   * @brief ConstNodeIterator to the first node
   * @return Iterator to the first node
   */
  ConstNodeIterator node_cbegin() const
  {
    return ConstNodeIterator(nodes_.cbegin());
  }
  /**
   * @brief ConstNodeIterator to behind the last node
   * @return Iterator to behind the last node
   */
 ConstNodeIterator node_cend() const
  {
    return ConstNodeIterator(nodes_.cend());
  }
  //@}

  ///////////////////////////////////////////////////////////
  //    Private member declarations
  ///////////////////////////////////////////////////////////

private:
  /**
   * @brief Auxiliary function. Creates an empty Graph using the deduced storage format.
   */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  // here using matrix
  GL_ENABLE_IF_MATRIX
#endif
  void construct()
  {
    matrix_t matrix(numNodes() * numNodes(), Edge());
    for (idx_t i = 0; i < numNodes(); ++i)
    {
      for (idx_t j = 0; j < numNodes(); ++j)
      {
        matrix[i * numNodes() + j].source(i);
        matrix[i * numNodes() + j].dest(j);
      }
    }
    edges_ = matrix;
  }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  /**
   * @brief Auxiliary function. Creates an empty Graph using an adjacency list storage format.
   */
  GL_ENABLE_IF_LIST
  void construct()
  {
    rootList_t list(numNodes());
    edges_ = list;
  }
#endif
  /**
   * @name checkRange
   * @brief Asserts that the given index/indecies is within the graph.
   */
  //@{
  /**
   * @brief Only one index that gets range checked.
   * @param idx1 Index that will be range checked
   */
  inline void checkRange(const idx_t& idx1) const
  {
    GL_ASSERT((0 <= idx1), (std::string("Negative index: ") + std::to_string(idx1) + std::string(" < 0")))
    GL_ASSERT((idx1 < numNodes()), ("Index " + std::to_string(idx1) + " is larger than the max: " + std::to_string(numNodes() - 1)))
  }

  /**
   * @brief Two indices ("edge") that get range checked.
   * @param idx1 First index that will be range checked
   * @param idx2 Second index that will be range checked.
   */
  inline void checkRange(const idx_t& idx1, const idx_t& idx2) const
  {
    checkRange(idx1);
    checkRange(idx2);
  }

};

} /* namespace gl */

#endif /* GL_GRAPH_HPP */