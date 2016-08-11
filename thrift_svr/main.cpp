#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/concurrency/ThreadManager.h>

#include "server_handler.h"

using namespace ::apache;

int main (int argc, char **argv) {
	// thread manager
	boost::shared_ptr<thrift::concurrency::ThreadManager> thread_mgr = \
		thrift::concurrency::ThreadManager::newSimpleThreadManager(10, 10);
	boost::shared_ptr<thrift::concurrency::PosixThreadFactory> thread_factory(
		new thrift::concurrency::PosixThreadFactory());
	thread_mgr->threadFactory(thread_factory);
	thread_mgr->start();

	// handler -> processor; protocol_factor
	boost::shared_ptr<LogicServiceHandler> handler(new LogicServiceHandler());
	boost::shared_ptr<thrift::TProcessor> processor(new ::ss::logic::LogicServiceProcessor(handler));  // assign UDT handler to thrift processor
	boost::shared_ptr<thrift::protocol::TProtocolFactory> protocol_facory(new thrift::protocol::TBinaryProtocolFactory());

	// start service
	//		processor, protocol_factory(这里选了binary)， port，
	//		started thread manager (containing thread_factory in the model of posix_thread)
	std::unique_ptr<thrift::server::TNonblockingServer> svr_ptr(
		new thrift::server::TNonblockingServer(processor, protocol_facory, 6444, thread_mgr));
	std::cout << "LogicService starts on port 6444" << std::endl;
	try {
		svr_ptr->serve();
	} catch (std::exception &e) {
		std::cerr << "svr_ptr serve failed; [" << e.what() << "]" << std::endl;
	}
	return 0;
}
