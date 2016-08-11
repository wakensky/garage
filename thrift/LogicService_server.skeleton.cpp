// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "LogicService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::ss::logic;

class LogicServiceHandler : virtual public LogicServiceIf {
 public:
  LogicServiceHandler() {
    // Your initialization goes here
  }

  void do_logic(Rsp& _return, const Req& req) {
    // Your implementation goes here
    printf("do_logic\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<LogicServiceHandler> handler(new LogicServiceHandler());
  shared_ptr<TProcessor> processor(new LogicServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

