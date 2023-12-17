// In the name of Allah

#include <iostream>
#include <memory>
#include <string>
#include "include/darc-rpc.hpp"
#include "msg_sample.hpp"
#include <fstream>
#include <windows.h>
using std::make_shared;
using namespace std;
int main()
{

    // Windows-> WinSock Initialization
    dc::socket_requirements::init();

    // create rpc_server with message types
    dc::rpc_server<msg_params, msg_result> server("127.0.0.1", 31311);

    const uint16_t first[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

    const uint16_t M_SUM = 0x0000;

    //    ofstream f;
    //    f.open("number_of_edes.txt");
    //    f<<0;
    //    f.close();

    int a=0;
    server.register_method(first[0], [](msg_params* input, msg_result* output) {
        output->value1 = static_cast<uint16_t>(input->a) + static_cast<uint16_t>(input->a);
        int b=input->a;
        ofstream f;
        f.open("number_of_edes.txt");
        f<<b;
        f.close();

        //برای اینکه از اول فایل را باز کند این را نوشتیم
        ofstream out;
        out.open("final_graph.txt");
        out.close();

    });

    int i=1;

    // مرحله حلقه انتقال
    while (i<5) {


        server.register_method(first[i], [](msg_params* input, msg_result* output) {
            ifstream r;
            r.open("number_of_edes.txt");
            string temp_number_of_edges;
            getline(r,temp_number_of_edges);
            r.close();
            int temp=stoi(temp_number_of_edges);
            cout<<"temp: "<<temp<<endl;
            temp--;
            ofstream w;
            w.open("number_of_edes.txt");
            w <<temp<<endl;
            w.close();
            if(temp<1)
                return 0;


            output->value1 = static_cast<uint16_t>(input->a) + static_cast<uint16_t>(input->a);
            int b=input->a;
            ofstream out;
            out.open("final_graph.txt", std::ios::app);
            out <<b<<endl;
            out.close();

        });

        i++;
    }






    //    server.register_method(first[1], [](msg_params* input, msg_result* output) {
    //        ifstream f("number_of_edes.txt");
    //        string number_of_edges;
    //        getline(f,number_of_edges);
    //        cout<<"number_of_edges"<<number_of_edges<<endl;

    //    });


    //    dc::socket_requirements::init();

    // create rpc_server with message types
    //    dc::rpc_server<msg_params, msg_result> server1("127.0.0.1", 31312);

    //    server1.register_method(first[2], [](msg_params* input, msg_result* output) {

    //        cout<<"i am server1: "<<endl;

    //    });


    // register another method


    //        for (int i = 0; i < 4; i++)
    //        {
    //            server.register_method(first[i], [](msg_params* input, msg_result* output) {
    //                output->value = static_cast<uint16_t>(input->a) +
    //                    static_cast<uint16_t>(input->b) +
    //                    static_cast<uint16_t>(input->c);
    //            });

    //      }



    // register method
    //const uint16_t M_SUM = 0x0000;
    //server.register_method(first[0], [](msg_params* input, msg_result* output) {
    //	output->value = static_cast<uint16_t>(input->a) +
    //		static_cast<uint16_t>(input->b) +
    //		static_cast<uint16_t>(input->c);
    //});

    // register another method
    //const uint16_t M_SUM_SQUARED = 0x0001;
    //server.register_method(first[1],
    //	[](msg_params* input, msg_result* output) {
    //	output->value = static_cast<uint16_t>(input->a) +
    //		static_cast<uint16_t>(input->b) +
    //		static_cast<uint16_t>(input->c);
    //	output->value = output->value * output->value;
    //	cout<<"SALAM"<<endl;
    //});

    // create TPC server, listen, accept client, and process requests
    server.run();

    // connection will be closed automatically on the destructor of (rpc_server)
    return 0;
}
