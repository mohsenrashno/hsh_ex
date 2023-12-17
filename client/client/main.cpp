

//#include "CXXGraph.hpp"
#include <memory>
#include <string>
#include <iostream>
#include "include/darc-rpc.hpp"
#include "msg_sample.hpp"

using std::make_shared;
using namespace std;

int** create_graph(int num_of_nodes, int min_weight_edges, int max_weight_edges)
{
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


    // int list_edges_betweens_nodes[num_of_edges][3];
    int **list_edges_betweens_nodes;
    int temp=num_of_edges+1;
    list_edges_betweens_nodes= new int*[num_of_edges];
    for(int i = 0; i<=num_of_edges; i++)
    {
        list_edges_betweens_nodes[i] = new int[3];
    }
    // sign for finish array
    list_edges_betweens_nodes[num_of_edges][0]=-2;
    for(int i = 0; i<num_of_edges; i++)
    {
        list_edges_betweens_nodes[i][0] = -1;
    }


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

        int random_wieght=0;
        while(1)
        {
            random_wieght = (rand() % max_weight_edges);
            if(random_wieght>=min_weight_edges)
                break;
        }
        list_edges_betweens_nodes[i][2] = random_wieght;

    }

    for(int i = 0; i<num_of_edges; i++)
    {
        std::cout << list_edges_betweens_nodes[i][0] <<" * " << list_edges_betweens_nodes[i][1] <<" * " << list_edges_betweens_nodes[i][2] <<endl;
    }

    int i= 0;
    while(list_edges_betweens_nodes[i][0]!=-2)
    {
        cout<<list_edges_betweens_nodes[i]<<" "<<list_edges_betweens_nodes[i][0]<<endl;
        i++;
    }
    std::cout << "i: "<<i<<endl;

    return list_edges_betweens_nodes;

}

int main() {

    cout<<"In the name Allah"<<endl<<endl;

    // question of user for number of vertex and min-max weight's edges.
    int vertex=0,min_weight=0,max_weight=0;

    int **graph;

    //const uint16_t *first;
    //first = new const uint16_t[4];
    const uint16_t first[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };


    dc::socket_requirements::init();
    dc::rpc_client client("127.0.0.1", 31311);

    if (client.connect()) {
        cout<<"Established Connection..."<<endl;
        cout<<"Please enter number of Vertex: ";
        cin>>vertex;
        cout<<endl<<"Please enter Min Wieght of Edges: ";
        cin>>min_weight;
        cout<<endl<<"Please enter Max Wieght of Edges: ";
        cin>>max_weight;
        graph=create_graph(vertex,min_weight,max_weight);

    }
    else
    {
        return 1;
    }

    int number_of_deges= 0;
    while(graph[number_of_deges][0]!=-2)
    {
        cout << graph[number_of_deges][0] <<" # " << graph[number_of_deges][1] <<" # " << graph[number_of_deges][2] <<endl;
        number_of_deges++;
        cout<<"number_of_deges: "<<number_of_deges<<endl;
    }
    const uint16_t M_SUM = 0x0000;

    cout<<"Final: "<<number_of_deges<<endl;
    //    int a=0;
    //    cin>>a;
    msg_params msg_in;
    msg_result msg_out;

    msg_in.a = number_of_deges;

    uint8_t* buffer[100];
    //	msg_in.deserialize = "aaadfsdf";
    if (!client.execute(first[0], &msg_in, &msg_out)) {
        return 1;
    }
    printf("sum: %" PRIu16 "\n", msg_out.value1);


    int i=0;
    while(i<25)
    {
        msg_in.a =  graph[i][0];
        msg_in.b =  graph[i][1];
        msg_in.c =  graph[i][2];
        int j=i+1;
        if (!client.execute(first[j], &msg_in, &msg_out)) {
            return 1;
        }
        printf("sum_next: %" PRIu16 "\n", msg_out.value1);
        cout<<endl;
        i++;
    }


    int a= 0;
    cin>>a;


    //    if (!client.execute(first[1], &msg_in, &msg_out)) {
    //        return 1;
    //    }

    //    dc::socket_requirements::init();
    //    dc::rpc_client client1("127.0.0.1", 31312);

    //    if (client1.connect()) {


    //    }
    //    else
    //    {
    //        return 1;
    //    }

    //    if (!client1.execute(first[2], &msg_in, &msg_out)) {
    //        cout<<"i am client1: "<<endl;
    //    }

    //    int a=0;
    //    cin>>a;



    // connection will be closed automatically on the destructor of (rpc_client)




    return 0;
}


//int main()
//{







//    int a;
//    cin >>a;

//    return 0;
//}


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
