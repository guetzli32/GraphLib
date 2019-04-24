#ifndef READ_YAML_HPP
#define READ_YAML_HPP

#include "../structures/Graph.hpp"
#include <fstream>
#include <variant>
#include <sstream>

namespace gl
{
namespace io
{

/**
  * @brief Template object to use with IO_CALL_ON_GRAPH
*/
#define IO_GRAPH (*arg)

/**
 * @brief Custom function on parsed graphs
 * @param g The graph (graph_variant_type) got from YAMLReader::get
 * @param func A normal line of c++ to be executed (use IO_GRAPH to template the graph object)
 */
#define IO_CALL_ON_GRAPH(g, func) std::visit([&](auto arg) { func; }, g)

/**
 * @brief Class to Read from a YAML file
 */
class YAMLReader
{
public:
    /**
     * @brief All possible variants of graphs
     */
    using graph_variant_type = std::variant<graphMdu *, graphMdd *, graphLdu *, graphLdd *,
                                            graphMfu *, graphMfd *, graphLfu *, graphLfd *,
                                            graphMiu *, graphMid *, graphLiu *, graphLid *>;
    /**
     * @brief Default constructor
     */
    YAMLReader() {}
    /**
     * @brief Construct with filename
     */
    YAMLReader(const char *filename);

    /**
     * @brief Set the Filename to use
     * @param filename Location of file to read from
     */
    void setFilename(const char *filename);

    /**
     * @brief Get the graph-variant
     * @return A variable containing a pointer to a graph variant
     */
    graph_variant_type get() { return graph_; }

    /**
     * @brief Reads the file, generates graph
     * This is automatically done in YAMLReader(const char *filename)
     */
    void read();

private:
    std::fstream stream_;      ///< the filestream to use
    graph_variant_type graph_; ///< the graph variant
};

YAMLReader::YAMLReader(const char *filename)
{
    stream_ = std::fstream(filename);
    graph_ = graph_variant_type(); // set to default
    GL_ASSERT(stream_.is_open(), "File could not be opened");
    read();
}

void YAMLReader::setFilename(const char *filename)
{
    stream_ = std::fstream(filename);
    GL_ASSERT(stream_.is_open(), "File could not be opened");
}

void YAMLReader::read()
{
    using idx_t = graphMdd::idx_t; // use idx_t from a graph
    // {{from,to},{weight, color}}
    using edge_t = std::pair<std::pair<idx_t, idx_t>, std::pair<double, gl::Color>>;

    // temp variables to store data while reading
    std::string value_type, storage_type, direction_type, graph_label;
    idx_t number_of_nodes;

    std::vector<edge_t> edges;
    std::vector<std::pair<idx_t, std::pair<double, const std::string>>> nodes;

    std::string line;
    while (getline(stream_, line))
    {
        // comments on lines
        if (line[0] == '#' || line.empty())
            continue;
        std::size_t delimiterPos = line.find(":");
        std::string name = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);
        // trim spaces
        value.erase(value.begin(), std::find_if(value.begin(), value.end(),
                                                std::not1(std::ptr_fun<int, int>(std::isspace))));
        if (name == "value_type")
        {
            value_type = value;
        }
        else if (name == "direction_type")
        {
            direction_type = value;
        }
        else if (name == "storage_type")
        {
            storage_type = value;
        }
        else if (name == "number_nodes")
        {
            number_of_nodes = std::stoi(value);
        }
        else if (name == "label")
        {
            graph_label = value;
        }
        else if (name == "edge")
        {
            std::stringstream ss(value);
            idx_t a, b;
            double weight = 1;
            ss >> a >> b;
            // if ss not empty, read weight
            if (!ss.eof())
            {
                ss >> weight;
            }
            gl::Color c(0, 0, 0);
            unsigned int hex;
            if (!ss.eof())
            {
                ss >> std::hex >> hex;
                c.hex(hex);
            }
            edges.push_back({{a, b}, {weight, c}});
        }
        else if (name == "node")
        {
            idx_t node;
            double cap;
            std::stringstream ss(value);
            ss >> node >> cap;
            std::string rest;
            getline(ss, rest);
            nodes.push_back({node, {cap, rest}});
        }
        else
        {
            GL_ASSERT(false, "Unrecognized option: " + line);
        }
    }

    // switch graph_ on current state from reading
    if (value_type == "double" && storage_type == "Matrix" && direction_type == "Undirected")
    {
        graph_ = new graphMdu(number_of_nodes, graph_label);
    }
    else if (value_type == "double" && storage_type == "Matrix" && direction_type == "Directed")
    {
        graph_ = new graphMdd(number_of_nodes, graph_label);
    }
    else if (value_type == "double" && storage_type == "List" && direction_type == "Undirected")
    {
        graph_ = new graphLdu(number_of_nodes, graph_label);
    }
    else if (value_type == "double" && storage_type == "List" && direction_type == "Directed")
    {
        graph_ = new graphLdd(number_of_nodes, graph_label);
    }
    else if (value_type == "float" && storage_type == "Matrix" && direction_type == "Undirected")
    {
        graph_ = new graphMfu(number_of_nodes, graph_label);
    }
    else if (value_type == "float" && storage_type == "Matrix" && direction_type == "Directed")
    {
        graph_ = new graphMfd(number_of_nodes, graph_label);
    }
    else if (value_type == "float" && storage_type == "List" && direction_type == "Undirected")
    {
        graph_ = new graphLfu(number_of_nodes, graph_label);
    }
    else if (value_type == "float" && storage_type == "List" && direction_type == "Directed")
    {
        graph_ = new graphLfd(number_of_nodes, graph_label);
    }
    else if (value_type == "int" && storage_type == "Matrix" && direction_type == "Undirected")
    {
        graph_ = new graphMiu(number_of_nodes, graph_label);
    }
    else if (value_type == "int" && storage_type == "Matrix" && direction_type == "Directed")
    {
        graph_ = new graphMid(number_of_nodes, graph_label);
    }
    else if (value_type == "int" && storage_type == "List" && direction_type == "Undirected")
    {
        graph_ = new graphLiu(number_of_nodes, graph_label);
    }
    else if (value_type == "int" && storage_type == "List" && direction_type == "Directed")
    {
        graph_ = new graphLid(number_of_nodes, graph_label);
    }
    else
    {
        GL_ASSERT(false, "Please enter valid data into config.");
    }

    // add all edges to the graph
    for (edge_t &e : edges)
    {
        IO_CALL_ON_GRAPH(graph_, IO_GRAPH.setEdge(e.first.first, e.first.second, e.second.first, e.second.second));
    }
    for (auto &n : nodes)
    {
        IO_CALL_ON_GRAPH(graph_, IO_GRAPH.updateNode(n.first, n.second.second, n.second.first));
    }
}

} /* namespace io */
} /* namespace gl */

#endif