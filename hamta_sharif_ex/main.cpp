#include "CXXGraph.hpp"
#include <memory>
#include <string>
#include <iostream>
#include "include/darc-rpc.hpp"
#include "msg_sample.hpp"

using std::make_shared;
using namespace std;

void create_graph(int num_of_nodes, int min_weight_edges, int max_weight_edges)
{
    CXXGraph::Node<int> *node[num_of_nodes];
    for(int i = 0; i<num_of_nodes; i++)
    {
        node[i]= new CXXGraph::Node<int>(to_string(i), i);
    }

    // make edges of graph, my strategy is max n(n-1)/2 and min n/2.
    // رویکرد من برای ساخت یال ها دراینجا این است که حداقل یال صفر نباشد و حداکثر هم مثل قاعده باشد
    srand(time(0));
    int N = (num_of_nodes*num_of_nodes-num_of_nodes)/2;
    int num_of_edges = 0;
    while(1)
    {
        num_of_edges = rand()% N;
        if(num_of_edges > N/10)
            break;
    }


    int list_edges_betweens_nodes[num_of_edges][3];
    for(int i = 0; i<num_of_edges; i++)
    {
        list_edges_betweens_nodes[i][0] = -1;
    }

    CXXGraph::UndirectedWeightedEdge<int> *edge[num_of_edges];
    CXXGraph::T_EdgeSet<int> edgeSet;

    for(int i = 0; i<num_of_edges; i++)
    {
        int node1=-1;
        int node2=-1;
        while(1)
        {
            bool verify = true;
            bool empty_list = false;
            while(1)
            {
                node1 = rand() % num_of_nodes ;
                node2 = rand() % num_of_nodes ;
                if(node1!=node2)
                        break;
            }

            for(int i = 0; i<num_of_edges; i++)
            {
                if(list_edges_betweens_nodes[i][0]==-1)
                {
                    empty_list = true;
                    break;
                }

                if((list_edges_betweens_nodes[i][0]==node1 && list_edges_betweens_nodes[i][1]==node2)||
               (list_edges_betweens_nodes[i][0]==node2 && list_edges_betweens_nodes[i][1]==node1))
                {
                    verify = false;
                    break;
                }
            }
            if(empty_list)
                break;
        }

        list_edges_betweens_nodes[i][0] = node1;
        list_edges_betweens_nodes[i][1] = node2;

        int random_wieght = min_weight_edges + (rand() % max_weight_edges);
        list_edges_betweens_nodes[i][2] = random_wieght;

        edge[i] = new CXXGraph::UndirectedWeightedEdge<int>(i, *node[node1], *node[node2], random_wieght);
        edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(*edge[i]));

    }

    CXXGraph::Graph<int> graph(edgeSet);
    auto res = graph.dijkstra(*node[2], *node[3]);

    for(int i = 0; i<num_of_edges; i++)
    {
        std::cout << list_edges_betweens_nodes[i][0] <<" * " << list_edges_betweens_nodes[i][1] <<" * " << list_edges_betweens_nodes[i][2] <<endl;
    }
    std::cout << *edge[0] << "\n";
    std::cout << *edge[1] << "\n";
    std::cout << "Dijkstra Result: " << res.result << "\n";


    int q = 0;


}

int main() {


  //  CXXGraph::UndirectedWeightedEdge<int> edge1(1, *node[0], *node[1], 2.0);
	dc::socket_requirements::init();

	// create rpc_server with message types
	dc::rpc_server<msg_params, msg_result> server("127.0.0.1", 31311);


	const uint16_t first[5] = { 1,2,3,4,5 };

   create_graph(5,12,20);
/*
  CXXGraph::Node<int> *node[2];
  node[0] = new CXXGraph::Node<int>("0", 0);
  node[1] = new CXXGraph::Node<int>("1", 1);
  node[2] = new CXXGraph::Node<int>("2", 2);
  node[3] = new CXXGraph::Node<int>("3", 3);

  CXXGraph::UndirectedWeightedEdge<int> edge1(1, *node[1], *node[2], 2.0);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, *node[2], *node[3], 2.0);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, *node[0], *node[1], 2.0);
  CXXGraph::UndirectedWeightedEdge<int> edge4(4, *node[0], *node[3], 1.0);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge4));

  // Can print out the edges for debugging
  std::cout << edge1 << "\n";
  std::cout << edge2 << "\n";
  std::cout << edge3 << "\n";
  std::cout << edge4 << "\n";

  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.dijkstra(*node[3], *node[1]);

  std::cout << "Dijkstra Result: " << res.result << "\n";

*/
  return 0;
}
