// In the name of Allah

#include <iostream>
#include <memory>
#include <string>
#include "include/darc-rpc.hpp"
#include "msg_sample.hpp"
using std::make_shared;
using namespace std;
int main()
{
    // Windows-> WinSock Initialization
        dc::socket_requirements::init();

        // create rpc_server with message types
        dc::rpc_server<msg_params, msg_result> server("127.0.0.1", 31311);

        const uint16_t first[15] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };



        server.register_method(first[0], [](msg_params* msg_vorodi, msg_result* msg_out) {
            msg_out->value1 =msg_vorodi->a;
            msg_out->value2 = msg_vorodi->b;
            msg_out->value3 = msg_vorodi->c;
        });

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
