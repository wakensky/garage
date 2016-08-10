INCLUDES = -I. -I.. \
	/usr/local/include/ \

LDFLAGS = -L. -L.. \
	-L/usr/local/lib/ \
	-lpthread \

CXXFLAGS = -g -O0 -std=c++11 -Werror

CXX = clang++
ROOT = .
OUTPUT =
BINARY = thrift_cli

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

all: $(BINARY)

$(BINARY) : $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $<

%.o : %.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

