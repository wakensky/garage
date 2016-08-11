INCLUDES := -I. \

CXXFLAGS := -g -O0 -std=c++11 -Werror

CXX := clang++
GEN_SRCS := logic_types.cpp LogicService.cpp
GEN_OBJS := $(GEN_SRCS:.cpp=.o)
LIB_TARGET := liblogic.a

all : $(GEN_SRCS) $(LIB_TARGET)

$(GEN_SRCS):
	thrift --gen cpp -out . logic.thrift

%.o : %.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $(INCLUDES) $<

$(LIB_TARGET) : $(GEN_OBJS)
	ar rcv $@ $^

clean:
	-rm $(LIB_TARGET) $(GEN_OBJS) *.h *.cpp
