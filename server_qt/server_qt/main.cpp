// In the name of Allah
#include <QCoreApplication>
#include <memory>
#include <string>
#include <iostream>
#include <memory>
#include <string>
#include "include/darc-rpc.hpp"
#include "msg_sample.hpp"
#include <fstream>
#include <sys/stat.h>
#include <iostream>
#include <windows.h>
#include <QProcess>

using std::make_shared;
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // winsock initial
    dc::socket_requirements::init();

    // create rpc_server with message types
    dc::rpc_server<msg_params, msg_result> server("127.0.0.1", 31311);

    // define message with limit!!!
    const uint16_t first[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

    //first create final_graph.txt for zero
    ofstream w;
    w.open("final_graph.txt");
    w.close();

    //first connect, save vertex and edges in file(get from client)
    server.register_method(first[0], [](msg_params* input, msg_result* output) {
        output->value1 = static_cast<uint16_t>(input->a) + static_cast<uint16_t>(input->a);
        int vertex=input->a;
        int edegs=input->b;
        string ins1 = to_string(vertex);
        string ins2 = to_string(edegs);
        string str1=ins1.append(" ");
        string final=str1.append(ins2);
        ofstream w;
        w.open("number_of_edes.txt");
        w<<final;
        w.close();
    });

    //prime loop for getting graph data and save it into file.
    int i=1;
    while (i<25) {
        server.register_method(first[i], [](msg_params* input, msg_result* output) {
            output->value1 = static_cast<uint16_t>(input->a) + static_cast<uint16_t>(input->a);
            int in1=input->a;
            int in2=input->b;
            int in3=input->c;
//            cout<<endl;
//            cout << in1<<"  "<<in2<<"  "<<in3;

            string ins1 = to_string(in1);
            string ins2 = to_string(in2);
            string ins3 = to_string(in3);
            string str1=ins1.append(" ");
            string str2=ins2.append(" ");
            string str3=str1.append(str2);
            string final=str3.append(ins3);

            ofstream w;
            w.open("final_graph.txt", std::ios::app);
            w <<final<<endl;
            w.close();
        });
        i++;
    }

    // run connection rcp
    server.run();

// we will with under code execute help app, but impossible!!!
//    QProcess process;
//    QString file("\"test_create_graph_cb.exe\"");
//    process.execute(file);

    return a.exec();
}
