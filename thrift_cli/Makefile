INCLUDES = -I. \

LDFLAGS = -L. -L../thrift/\
	-lpthread \
	-llogic \
	-lthrift \
	-lthriftnb \
	-levent \

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
	$(CXX) -o $@ $(LDFLAGS) $^

%.o : %.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

clean:
	-rm *.o *.d $(BINARY)
