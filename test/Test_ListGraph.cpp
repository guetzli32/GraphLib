#include <graphlib/gl>

int main(int argc, char const *argv[])
{

  gl::graphLid g (5,"ListGraph");
  g.setEdge(2,1,8); // initial set
  g.setEdge(1,0);   // set as simple undirected
  g.setEdge(2,0,5);
  g.numNodes();
  std::cout << "numNodes: " << g.numNodes() << std::endl
            << g << std::endl;
  g.updateEdge(1,0,5); // update weight via updateEdge
  g.updateEdge(2,1,gl::Color(0x123456)); // update color via updateEdge
  g.updateEdge(1,0,5,gl::Color("red")); // update both via updateEdge
  
  auto neighbours_of_2 = g.getNeighbours(2);
  auto neighbourWeights_of_2 = g.getNeighbourWeights(2);

  std::cout << "Neighbours of 2: ";
  for (auto x : neighbours_of_2) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
  for (auto x : neighbourWeights_of_2) {
    std::cout << "(" << x.first << "," << x.second << ") ";
  }
  std::cout << std::endl;
  std::cout << "Degree of 2: " << g.getNodeDegree(2) << std::endl;
  g.delEdge(2,0);   // remove edge
  std::cout << "deleted 2->0\n";
  try {
    g.delEdge(2,4);   // triggers assert if compiled
  } catch (const std::runtime_error& e) {
    std::cout << "Caught exception: " << e.what() << "\n";
  }
  g.addEdgesFromFile("test/Input_singleEdge"); // assumes running from build folder

  try {
    g.setEdge(1000,2,1);  // test out of range check
  } catch (const std::runtime_error& e) {
    std::cout << "Caught exception: " << e.what() << "\n";
  }
  try {
    g.setEdge(2,1,8); // test setting a previously created edge
  } catch (const std::runtime_error& e) {
    std::cout << "Caught exception: " << e.what() << "\n";
  }
  std::cout << std::endl << g << std::endl;

  // ConstEdgeIterator test
  for (auto it = g.edge_cbegin(); it != g.edge_cend(); ++it) {
    std::cout << "Weight of edge (" << it->source() << "->" << it->dest() << ") is " << it->weight() << "\n";
  }
  std::cout << std::endl;
  // EdgeIterator test
  for (auto it = g.edge_begin(); it != g.edge_end(); ++it) {
    it->weight(6);
    std::cout << "Weight of edge (" << it->source() << "->" << it->dest() << ") is " << it->weight() << "\n";
  }
  std::cout << std::endl;
  // ConstNodeIterator test
  for (auto it = g.node_cbegin(); it != g.node_cend(); ++it) {
    std::cout << "InDegree of node " << it->id() << " is " << it->inDegree() << "\n";
  }
  std::cout << std::endl;
  // NodeIterator test
  for (auto it = g.node_cbegin(); it != g.node_cend(); ++it) {
    std::cout << "outDegree of node " << it->id() << " is " << it->outDegree() << "\n";
  }
  std::cout << std::endl;

  return 0;
}
