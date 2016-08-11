#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include "../thrift/LogicService.h"

using namespace ::apache;

int main(int argc, char ** argv) {
	// socket
	boost::shared_ptr<thrift::transport::TSocket> socket_ptr(
		new thrift::transport::TSocket("127.0.0.1", 6444));
	socket_ptr->setConnTimeout(10);  // ms
	socket_ptr->setSendTimeout(10);  // ms
	socket_ptr->setRecvTimeout(100);  // ms

	// transport (only framed could be used for nonblocking server)
	boost::shared_ptr<thrift::transport::TTransport> transport(new thrift::transport::TFramedTransport(socket_ptr));

	// protocol
	boost::shared_ptr<thrift::protocol::TBinaryProtocol> protocol(new thrift::protocol::TBinaryProtocol(transport));

	// query
	try {
		::ss::logic::Req req;
		::ss::logic::Rsp rsp;
		req.__set_msg("logic_request_from_wudi");
		transport->open();
		::ss::logic::LogicServiceClient client(protocol);
		client.do_logic(rsp, req);
		transport->close();

		std::cout << "rsp status[" << rsp.status << "]" << std::endl;
	} catch (std::exception &e) {
		std::cerr << "LogicServiceClient failed since [" << e.what() << "]" << std::endl;
	}
	return 0;
}
