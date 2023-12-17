#include "CXXGraph.hpp"
#include <memory>
#include <string>
#include <iostream>

using std::make_shared;
using namespace std;
int *cal_num_vertex_edges()
{
    int *temp=new int[2];
            ifstream r;
            r.open("number_of_edes.txt");
            string temp_number_of_vertex;
            string temp_number_of_edges;
            while (r>>temp_number_of_vertex>>temp_number_of_edges)
	{
	    int tmp1=stoi(temp_number_of_vertex);
	    int tmp2=stoi(temp_number_of_edges);
	    temp[0]=tmp1;
	    temp[1]=tmp2;
	    r.close();
	    return temp;
	}
}

int **cal_list(int num_of_edges)
{
    int **list_edges_betweens_nodes=new int*[num_of_edges];
    for(int i=0; i<num_of_edges; i++)
    {
        list_edges_betweens_nodes[i]=new int[3];
    }
            ifstream r;
            r.open("final_graph.txt");
            string node1;
            string node2;
            string weight_edge;
            int i=0;
            while (r>>node1>>node2>>weight_edge)
	{
	    if(i==num_of_edges)
            break;
	    int tmp1=stoi(node1);
	    int tmp2=stoi(node2);
	    int tmp3=stoi(weight_edge);
	    list_edges_betweens_nodes[i][0]=tmp1;
	    list_edges_betweens_nodes[i][1]=tmp2;
	    list_edges_betweens_nodes[i][2]=tmp3;

	   i++;
	}
	r.close();
	 return list_edges_betweens_nodes;

}

void create_graph()
{


    int *temp1=cal_num_vertex_edges();
    int num_of_nodes=temp1[0];
    int num_of_edges=temp1[1];

    CXXGraph::Node<int> *node[num_of_nodes];
    for(int i = 0; i<num_of_nodes; i++)
    {
        node[i]= new CXXGraph::Node<int>(to_string(i), i);
    }

    int **list_edges_betweens_nodes=cal_list(num_of_edges);
    for(int i = 0; i<num_of_edges; i++)
    {
        cout<<list_edges_betweens_nodes[i][0]<<" "<<list_edges_betweens_nodes[i][1]<<" "<<list_edges_betweens_nodes[i][2]<<endl;
    }

    CXXGraph::UndirectedWeightedEdge<int> *edge[num_of_edges];
    CXXGraph::T_EdgeSet<int> edgeSet;

    for(int i = 0; i<num_of_edges; i++)
    {
/*
        list_edges_betweens_nodes[i][0] = node1;
        list_edges_betweens_nodes[i][1] = node2;

        int random_wieght = min_weight_edges + (rand() % max_weight_edges);
        list_edges_betweens_nodes[i][2] = random_wieght;
*/
        edge[i] = new CXXGraph::UndirectedWeightedEdge<int>(i, *node[list_edges_betweens_nodes[i][0]], *node[list_edges_betweens_nodes[i][1]], list_edges_betweens_nodes[i][2]);
        edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(*edge[i]));

    }

    CXXGraph::Graph<int> *grf;
    grf=new CXXGraph::Graph<int>(edgeSet);
    auto res= grf->dijkstra(*node[1], *node[3]);
    std::cout << "--------------" <<"\n\n";


    while(1)
    {
        cout<<"Calculate Dijkstra: "<<endl;
        cout<<"Enter first node: ";
        int a=0;
        cin>>a;
        cout<<endl;
        cout<<"Enter seccond node: ";
        int b=0;
        cin>>b;
        auto res= grf->dijkstra(*node[a], *node[b]);
        std::cout << "Dijkstra Result: " << res.result << "\n";
    }

   // auto res = graph.dijkstra(*node[1], *node[3]);


    for(int i = 0; i<num_of_edges; i++)
    {
        std::cout << list_edges_betweens_nodes[i][0] <<" * " << list_edges_betweens_nodes[i][1] <<" * " << list_edges_betweens_nodes[i][2] <<endl;
    }

  //  std::cout << "Dijkstra Result: " << res.result << "\n";



}

int main() {

	const uint16_t first[5] = { 1,2,3,4,5 };

	create_graph();



   /* int i= 0;
    while(graph[i][0]!=-2)
    {
       cout << graph[i][0] <<" * " << graph[i][1] <<" # " << graph[i][2] <<endl;
        i++;
    }
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
