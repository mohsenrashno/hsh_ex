// In the name of Allah

#include <iostream>
#include <memory>
#include <string>
#include "include/darc-rpc.hpp"
#include "msg_sample.hpp"
#include <fstream>
#include <windows.h>
#include <sys/stat.h>

using std::make_shared;
using namespace std;

inline bool exists_test0 (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}
int main()
{



    // Windows-> WinSock Initialization
    dc::socket_requirements::init();

    // create rpc_server with message types
    dc::rpc_server<msg_params, msg_result> server("127.0.0.1", 31311);

    const uint16_t first[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

    const uint16_t M_SUM = 0x0000;


    int a=0;
    ofstream w;
    w.open("final_graph.txt");
    w.close();

    //    });
    server.register_method(first[0], [](msg_params* input, msg_result* output) {
        output->value1 = static_cast<uint16_t>(input->a) + static_cast<uint16_t>(input->a);
        int b=input->a;
        ofstream f;
        f.open("number_of_edes.txt");
        f<<b;
        f.close();

    });

    int i=1;

    // مرحله حلقه انتقال
    while (i<25) {


        server.register_method(first[i], [](msg_params* input, msg_result* output) {
            output->value1 = static_cast<uint16_t>(input->a) + static_cast<uint16_t>(input->a);
            int in1=input->a;
            int in2=input->b;
            int in3=input->c;
            cout<<endl;
            cout << in1<<"  "<<in2<<"  "<<in3;

            string ins1 = to_string(in1);
            string ins2 = to_string(in2);
            string ins3 = to_string(in3);

            string str1=ins1.append(" ");
            string str2=ins2.append(" ");
            string str3=str1.append(str2);
            string final=str3.append(ins3);

            ofstream out;
            out.open("final_graph.txt", std::ios::app);
            out <<final<<endl;
            out.close();

        });

        i++;
    }

    cout<<"Finish_While"<<endl;





    //        if(temp>1)
    //        {
    //            cout<<"int temp=stoi(temp_number_of_edges);"<<temp<<endl;
    //            server.register_method(first[i], [](msg_params* input, msg_result* output) {
    //                output->value1 = static_cast<uint16_t>(input->a) + static_cast<uint16_t>(input->a);
    //                int b=input->a;
    //                ofstream out;
    //                out.open("final_graph.txt", std::ios::app);
    //                out <<4<<endl;
    //                out.close();

    //                ifstream r;
    //                r.open("number_of_edes.txt");
    //                string temp_number_of_edges;
    //                getline(r,temp_number_of_edges);
    //                r.close();
    //                int temp=stoi(temp_number_of_edges);
    //                //cout<<"temp: "<<temp<<endl;
    //                temp--;
    //                ofstream w;
    //                w.open("number_of_edes.txt");
    //                w <<temp<<endl;
    //                w.close();
    //            });
    //        }


    //        server.register_method(first[i], [](msg_params* input, msg_result* output) {
    //            ifstream r;
    //            r.open("number_of_edes.txt");
    //            string temp_number_of_edges;
    //            getline(r,temp_number_of_edges);
    //            r.close();
    //            int temp=stoi(temp_number_of_edges);
    //            cout<<"temp: "<<temp<<endl;
    //            temp--;
    //            ofstream w;
    //            w.open("number_of_edes.txt");
    //            w <<temp<<endl;
    //            w.close();
    //            if(temp<1)
    //                return 0;

    //            output->value1 = static_cast<uint16_t>(input->a) + static_cast<uint16_t>(input->a);
    //            int b=input->a;
    //            ofstream out;
    //            out.open("final_graph.txt", std::ios::app);
    //            out <<b<<endl;
    //            out.close();

    //        });

    //   i++;
//            ifstream r;
//            r.open("number_of_edes.txt");
//            string temp_number_of_edges;
//            getline(r,temp_number_of_edges);
//            r.close();
//            int temp=stoi(temp_number_of_edges);
    //        cout<<"temp: "<<temp<<endl;
    //        temp--;
    //        ofstream w;
    //        w.open("number_of_edes.txt");
    //        w <<temp<<endl;
    //        w.close();
    //        if(temp<1)
    //            break;







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
