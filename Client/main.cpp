#include "messageP.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <iostream>
int main()
{
    MessageP msg;
    msg.set_id("unique");
    std::cout << msg.id() << std::endl;
    return 0;
}
