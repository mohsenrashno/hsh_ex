// In the name of Allah
#include <QCoreApplication>
#include "CXXGraph.hpp"
#include <memory>
#include <string>
#include <iostream>

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
        if(num_of_edges > N/2)
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
    auto res = graph.dijkstra(*node[1], *node[3]);

    for(int i = 0; i<num_of_edges; i++)
    {
        std::cout << list_edges_betweens_nodes[i][0] <<" * " << list_edges_betweens_nodes[i][1] <<" * " << list_edges_betweens_nodes[i][2] <<endl;
    }
    std::cout << *edge[0] << "\n";
    std::cout << *edge[1] << "\n";
    std::cout << "Dijkstra Result: " << res.result << "\n";


    int q = 0;


}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
