// In the name of Allah
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

    int **list_edges_betweens_nodes;
    // +1 --> because one elemet for sending vertex and edges.
    int temp=num_of_edges+1;
    list_edges_betweens_nodes= new int*[num_of_edges];
    for(int i = 0; i<=num_of_edges; i++)
    {
        list_edges_betweens_nodes[i] = new int[3];
    }
    // sign for finish array --> because choose randomly
    list_edges_betweens_nodes[num_of_edges][0]=-2;
    for(int i = 0; i<num_of_edges; i++)
    {
        list_edges_betweens_nodes[i][0] = -1;
    }


    // algorithm for makeing graph
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

    //    for(int i = 0; i<num_of_edges; i++)
    //    {
    //        std::cout << list_edges_betweens_nodes[i][0] <<" * " << list_edges_betweens_nodes[i][1] <<" * " << list_edges_betweens_nodes[i][2] <<endl;
    //    }

    //    int i= 0;
    //    while(list_edges_betweens_nodes[i][0]!=-2)
    //    {
    //        cout<<list_edges_betweens_nodes[i]<<" "<<list_edges_betweens_nodes[i][0]<<endl;
    //        i++;
    //    }
    //    std::cout << "i: "<<i<<endl;

    return list_edges_betweens_nodes;

}

int main() {

    cout<<"In the name Allah"<<endl<<endl;

    // variable for elemet of graph
    int vertex=0,min_weight=0,max_weight=0;

    int **graph;
    // define message with limit!!!
    const uint16_t first[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

    // setting and initialing for rpc connection
    dc::socket_requirements::init();
    dc::rpc_client client("127.0.0.1", 31311);

    //after question of user for number of vertex and min-max weight's edges.
    if (client.connect()) {
        cout<<"Established Connection..."<<endl;
        cout<<"Please enter number of Vertex: ";
        cin>>vertex;
        cout<<endl<<"Please enter Min Wieght of Edges: ";
        cin>>min_weight;
        cout<<endl<<"Please enter Max Wieght of Edges: ";
        cin>>max_weight;
        if(min_weight>=max_weight)
        {
            cout<<endl<<"!!!Min must little than Max!!!"<<endl;
            cout<<endl<<"press a key to exit: "<<endl;
            int a=0;
            cin>>a;
            return 0;
        }
        graph=create_graph(vertex,min_weight,max_weight);
    }
    else
    {
        return 1;
    }

    int number_of_deges= 0;
    while(graph[number_of_deges][0]!=-2)
    {
        //        cout << graph[number_of_deges][0] <<" # " << graph[number_of_deges][1] <<" # " << graph[number_of_deges][2] <<endl;
        number_of_deges++;
        //        cout<<"number_of_deges: "<<number_of_deges<<endl;
    }

    // variable for sending, recieving data from rcp connection.
    msg_params msg_in;
    msg_result msg_out;

    //set vertex and edges for sending to server.
    msg_in.a = vertex;
    msg_in.b = number_of_deges;

    //sending first datat to server
    if (!client.execute(first[0], &msg_in, &msg_out)) {
        return 1;
    }

    // prime loop to sending graph.
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
        //        printf("sum_next: %" PRIu16 "\n", msg_out.value1);
        //        cout<<endl;
        i++;
    }

    //    int a= 0;
    //    cin>>a;

    return 0;
}
