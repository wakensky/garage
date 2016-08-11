#include "server_handler.h"

void LogicServiceHandler::do_logic(::ss::logic::Rsp &rsp, const ::ss::logic::Req &req) {
	rsp.status = "success; [";
	rsp.status += req.msg;
	rsp.status += "]";
}
