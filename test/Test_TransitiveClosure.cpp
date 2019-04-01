#include <graphlib/gl>

int main(int argc, char const *argv[])
{
  using graph = gl::MGraph<int>;
  graph g(8);
  g.readFile("test/Input_graph8"); // assumes running from project root folder
  std::cout << g << std::endl;
  graph::ordered_list_t tc;
  std::cout << "Transitive closure of every node:\n";
  for(graph::idx_t i = 0; i < g.numNodes(); i++)
  {
    tc = gl::algorithm::transitiveClosure(g, i);
    std::cout << i << ": ";
    gl::io::printContainer(tc);
  }
  return 0;
}
