# thrift --gen cpp -r -o .
namespace cpp ss.logic

struct Req {
	1: optional string msg = "",
}

struct Rsp {
	1: optional string status = "unknown",
}

service LogicService {
	Rsp do_logic(1:Req req),
}
