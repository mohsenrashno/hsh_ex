#include <iostream>
#include <iostream>
#include "include/darc-rpc.hpp"
#include "msg_sample.hpp"
using namespace std;

int main()
{
    cout<<"In the name Allah"<<endl<<endl;


    // question of user for number of vertex and min-max weight's edges.
    int vertex=0,min_weight=0,max_weight=0;



    //const uint16_t *first;
    //first = new const uint16_t[4];
    const uint16_t first[15] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

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

    }
    else
    {
       return 1;
    }

    msg_params msg_in;
    msg_result msg_out;

    msg_in.a = vertex;
    msg_in.b = min_weight;
    msg_in.c = max_weight;

    //uint8_t a, b, c;

    if (!client.execute(first[0], &msg_in, &msg_out)) {
        return 1;
    }

        cout<<endl;
        printf("sum1: %" PRIu16 "\n", msg_out.value1);
        cout<<endl;
        printf("sum2: %" PRIu16 "\n", msg_out.value2);
        cout<<endl;
        printf("sum3: %" PRIu16 "\n", msg_out.value3);

        cout <<"NEXT"<<endl;

        msg_in.a = 14;
        msg_in.b = 24;
        msg_in.c = 34;

        if (client.execute(first[0], &msg_in, &msg_out)) {
            while (1) {
                if(msg_out.value1!=-1)
                    break;
            }
        }

        printf("sum1: %" PRIu16 "\n", msg_out.value1);
        cout<<endl;
        printf("sum2: %" PRIu16 "\n", msg_out.value2);
        cout<<endl;
        printf("sum3: %" PRIu16 "\n", msg_out.value3);




//    for (int i = 0; i < 4; i++)
//    {
//        msg_in.a = i;
//        msg_in.b = i;
//        msg_in.c = i;

//        if (!client.execute(first[i], &msg_in, &msg_out)) {
//            return 1;
//        }
//            printf("sum: %" PRIu16 "\n", msg_out.value);

//    }


    /*if (!client.execute(first[1], &msg_out, &msg_out)) {
        return 1;
    }
    printf("sum: %" PRIu16 "\n", msg_out.value);

    msg_in.a = 2;
    msg_in.b = 4;
    msg_in.c = 5;
    if (!client.execute(first[0], &msg_in, &msg_out)) {
        return 1;
    }
    printf("sum^2: %" PRIu16 "\n", msg_out.value);*/

    // connection will be closed automatically on the destructor of (rpc_client)

   int a;
   cin >>a;

    return 0;
}
