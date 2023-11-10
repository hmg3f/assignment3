CXX=g++
CXXFLAGS=-g

SRCS=main.cpp expmanager.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: output

output: $(OBJS)
	$(CXX) $(CXXFLAGS) -o output $(OBJS)

main.o: main.cpp expmanager.hpp myqueue.hpp

expmanager.o: expmanager.cpp expmanager.hpp

clean:
	rm -f $(OBJS) myqueue.o

distclean: clean
	rm output
