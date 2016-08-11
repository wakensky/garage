INCLUDES := -I. -Ithrift/ \

LDFLAGS := -L. -Lthrift/ \
	-lpthread \

CXXFLAGS := -g -O0 -std=c++11 -Werror

CXX := clang++
BINARY := program
SRCS := $(wildcard *.cc)
OBJS := $(SRCS:.cc=.o)

all : $(BINARY)

$(BINARY):$(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $<

%.o : %.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $(INCLUDES) $<

clean:
	-rm $(OBJS)
	-rm $(BINARY)
