#pragma once

#include "../thrift/LogicService.h"

class LogicServiceHandler : virtual public ::ss::logic::LogicServiceIf {
public:
	LogicServiceHandler() = default;

	// 关键要实现这个 public interface
	virtual void do_logic(::ss::logic::Rsp &rsp, const ::ss::logic::Req &req);
};
