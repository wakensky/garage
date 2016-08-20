INCLUDES = -I. \

LDFLAGS = -L. \
	-lpthread \

CXX = clang++
BUILD_TIME = $(shell date +%Y%m%d-%H:%M:%S)
CXXFLAGS = -g -O0 -Wall -Werror -std=c++11 -DBUILD_TIME=$(BUILD_TIME)

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

# the FIRST target is the default target
all: $(BINARY)

%.o : %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INCLUDES)
	$(CXX) -MM $(CXXFLAGS) $< > $*.d

clean:
	-rm *.o *.d $(BINARY)

$(BINARY) : $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)
