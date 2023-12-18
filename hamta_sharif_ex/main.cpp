// In the name of Allah
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
    // calculate vertex and edegs form stored file.
    int *temp1=cal_num_vertex_edges();
    int num_of_nodes=temp1[0];
    int num_of_edges=temp1[1];

    // making and naming node for graph.
    CXXGraph::Node<int> *node[num_of_nodes];
    for(int i = 0; i<num_of_nodes; i++)
    {
        node[i]= new CXXGraph::Node<int>(to_string(i), i);
    }

    // create and showing list edegs from stored file.
    int **list_edges_betweens_nodes=cal_list(num_of_edges);
    cout<<"node1"<<" "<<"node2"<<" "<<"      edege"<<endl;
    for(int i = 0; i<num_of_edges; i++)
    {
        cout<<"   "<<list_edges_betweens_nodes[i][0]<<"    "<<list_edges_betweens_nodes[i][1]<<"    ---->  "<<list_edges_betweens_nodes[i][2]<<endl;
    }

    // making struct for edges.
    CXXGraph::UndirectedWeightedEdge<int> *edge[num_of_edges];
    CXXGraph::T_EdgeSet<int> edgeSet;

    // assign list of edges for struct' edges.
    for(int i = 0; i<num_of_edges; i++)
    {
        edge[i] = new CXXGraph::UndirectedWeightedEdge<int>(i, *node[list_edges_betweens_nodes[i][0]], *node[list_edges_betweens_nodes[i][1]], list_edges_betweens_nodes[i][2]);
        edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(*edge[i]));
    }

    // define grap of before data.
    CXXGraph::Graph<int> *grf;
    grf=new CXXGraph::Graph<int>(edgeSet);
    std::cout << "------------------";

    // making loop for show and calculate minimum path betwwen two nodes.
    while(1)
    {
        cout <<endl<<endl;
        cout<<"Calculate Dijkstra: "<<endl;
        cout<<"1th node: ";
        int a=0;
        cin>>a;
        cout<<endl;
        cout<<"2th node: ";
        int b=0;
        cin>>b;
        auto res= grf->dijkstra(*node[a], *node[b]);
        cout << "Dijkstra Result: " << res.result << "\n";
    }
}

int main() {

    // create graph for calculate mimimum of path(Dijkstra).
	create_graph();

  return 0;
}
